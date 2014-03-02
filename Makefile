# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_28_exe


PROJECT_ROOT := ./
EXTERNAL_ROOT=$(PROJECT_ROOT)external
SRCDIR = $(PROJECT_ROOT)src
OBJDIR = $(PROJECT_ROOT)myobjs
BINDIR = $(PROJECT_ROOT)mybins
DOCDIR = $(PROJECT_ROOT)doc
SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL 
NewLI = -lCS296test -lBox2D -lglui -lglut -lGLU -lGL 


#CPPFLAGS =-g -O3 -Wall -fno-strict-aliasing this is the original line
CPPFLAGS =-g -Wall -fno-strict-aliasing -p
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib
NewLD+=-L $(PROJECT_ROOT)mylibs -L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SHARED_LIB =TRUE
ifeq ($(SHARED_LIB) ,FALSE)
	decider=newtargeta
else
	decider=newtargetso
endif
########################################
WORD=cmake ../
.PHONY: setup exe exelib doc report data plot

exe: setup $(BINDIR)/$(TARGET)
exelib: setup $(OBJS) $(decider)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "cs296_28_exelib"
	@if [ $(SHARED_LIB) == FALSE ];then $(CC) -o cs296_28_exelib $(NewLD) $(OBJDIR)/main.o $(NewLI);\
	else $(CC) -o cs296_28_exelib $(NewLD) $(OBJDIR)/main.o $(NewLI); fi;
 	
#$(BINDIR)/$(TARGET)
#newtarget: ifeq ($(SHARED_LIB), TRUE)
#  	newtargeta 
#else 
#	newtargetso 
#endif
##################################################################
###############lab06 additions ####################################
debug_prof: WORD=cmake -DCMAKE_BUILD_TYPE=Debug ../
debug_prof: exe
	@./mybins/cs296_28_exe 100000; \
	gprof ./mybins/cs296_28_exe > g28_debug_prof.dat
release_prof: WORD=cmake -DCMAKE_BUILD_TYPE=Release ../
release_prof: CPPFLAGS+= -O3
release_prof: exe
	@./mybins/cs296_28_exe 100000; \
	gprof ./mybins/cs296_28_exe > g28_release_prof.dat
#########################################################################
newtargeta:
	@cd $(OBJDIR);ar -cq libCS296test.a [!main]*.o;cd ..;mv $(OBJDIR)/libCS296test.a $(PROJECT_ROOT)mylibs/libCS296test.a;
newtargetso:
	@cd $(OBJDIR); gcc -shared -Wl,-soname,libCS296test.so -o libCS296test.so [!m]*.o;cd ..; mv $(OBJDIR)/libCS296test.so $(PROJECT_ROOT)mylibs/libCS296test.so;


-include $(OBJS:.o=.d)
$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp 
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -fPIC -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) $(CPPFLAGS) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err


setup:
	@$(ECHO) "Setting up Compilation..."
	@mkdir -p myobjs
	@mkdir -p mybins
	@mkdir -p mylibs
	@$(ECHO) $(PROJECT_ROOT)
	@if [ -f $(PROJECT_ROOT)external/include/Box2D/Box2D.h ] && [ -f $(PROJECT_ROOT)external/lib/Box2D/Box2D.h ];\
	then $(ECHO) -n "Done...";\
	else cd $(PROJECT_ROOT)external/src; tar xzf ./Box2D.tgz; cd Box2D; mkdir build296;cd build296;$(WORD); make; make install;\
	cd $(PROJECT_ROOT);\
	fi;
clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~
	@$(RM) -f $(PROJECT_ROOT)data/* #this is edited
	@$(RM) -f $(PROJECT_ROOT)plots/*
	@$(RM) -f $(PROJECT_ROOT)scripts/fit.log
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(PROJECT_ROOT)mylibs $(BINDIR) $(DOCDIR)/html cs296_28_exelib $(PROJECT_ROOT)obj $(PROJECT_ROOT)bin $(PROJECT_ROOT)external/include/* $(PROJECT_ROOT)external/lib/* $(PROJECT_ROOT)external/src/Box2D
	@cd ./doc/;$(RM) -f cs296_report_28.aux cs296_report_28.bbl cs296_report_28.blg cs296_report_28.log cs296_report_28.pdf dubdubexec-eps-converted-to.pdf sqpendulumexe-eps-converted-to.pdf sqpendulumnotexec-eps-converted-to.pdf toppledexec-eps-converted-to.pdf topplingrod-eps-converted-to.pdf dubdubdub-eps-converted-to.pdf g28_prof_report.aux g28_prof_report.log g28_prof_report.pdf
	@$(RM) -f gmon.out g28_debug_prof.dat g28_release_prof.dat
doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"
report:
	@cd ./doc/;pdflatex cs296_report_28;\
	bibtex cs296_report_28;\
	pdflatex cs296_report_28;\
	bibtex cs296_report_28;\
	pdflatex cs296_report_28;\
	bibtex cs296_report_28;\
	pdflatex g28_prof_report.tex;\
	pdflatex g28_prof_report.tex
data: exe
	@cd scripts;\
	./g28_gen_data.sh;\
	./g28_gen_csv.sh;\
	./g28_gen_data_csv.sh;\
	./g28_gen_data_ranndom.sh
plot: data
	@cd scripts;\
	./average.sh;\
	gnuplot g28_plot01.gpt;\
	gnuplot g28_plot02.gpt;\
	$(RM) -f ../data/average.csv;\
	./dev.sh;\
	gnuplot g28_plot03.gpt;\
	$(RM) -f ../data/average.csv;\
	./highest.sh;\
	gnuplot g28_plot04.gpt;\
	$(RM) -f ../data/highest.csv;\
	./average4andrandom.sh;\
	gnuplot g28_plot05.gpt;\
	$(RM) -f ../data/average4andrandom.csv
