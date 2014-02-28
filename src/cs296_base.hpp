/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  //! What is the difference between a class and a struct in C++?
  class base_sim_t;
  struct settings_t;
  
  //! Why do we use a typedef
  typedef base_sim_t* sim_create_fcn(); 

  //! Simulation settings. Some can be controlled in the GUI.
  /*!
   * \li 
   */
  struct settings_t
  {
    //! Notice the initialization of the class members in the constructor
    //! How is this happening?
     /*! About the constructor \b seeting_t()
      * \li \b view_center(0.0f, 20.0f) :this is the center of our viewpoint(GUI)
      *  \li \b hz(90.0f),
      * \li \b velocity_iterations(8):this is velocity iterations on screen
      * \li \b position_iterations(3) :this is the position iterations on screen
      * \li \b draw_shapes(1) :this is to draw shapes by default
      * \li \b draw_joints(1) :this is to show joints by default
      * \li \b draw_AABBs(0) :AABBs are Axis Aligned Bounding Boxes.
      * \li \b draw_pairs(1)
      * \li \b draw_contact_points(1)
      * \li \b draw_contact_normals(1)
      * \li \b draw_contact_forces(0)
      * \li \b draw_friction_forces(0)
      * \li \b draw_COMs(0)
      * \li \b draw_stats(0) :this call is to print the statistics on the screen
      * \li \b draw_profile(0) :this call prints the profile statistics on screen
      * \li \b enable_warm_starting(0)
      * \li \b enable_continuous(1): 
      * \li \b enable_sub_stepping(1):enables substepping
      * \li \b pause(0):auto pause at the start
      * 
      
      *  \li \b position_iterations is of \b Data \b Type: \b int32 .It determines the  number of times position is corrected per frame.
     
     */ 
    settings_t() :
      view_center(0.0f, 20.0f),
      hz(60.0f),
     
      velocity_iterations(8),
      position_iterations(3),
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(0),
      draw_friction_forces(0),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    
    b2Vec2 view_center;//!< \b view_center is of \b Data \b Type: \b b2Vec2.It acts as the center of the simulation when it starts.
    float32 hz;//!< \b hz is of \b Data \b Type: \b float32.
    int32 velocity_iterations;//!< \b velocity_iterations is of \b Data \b Type: \b int32 .It determines the  number of times velocity is corrected per frame.
    int32 position_iterations;//!<\b position_iterations is of \b Data \b Type: \b int32 .It determines the  number of times position is corrected per frame.
    int32 draw_shapes;//!< \b draw_shapes is of \b Data \b Type: \b int32. It displays the objects in the simulation.
    int32 draw_joints;//!< \b draw_joints is of \b Data \b Type: \b int32. It displays the joints in the simulation.
    int32 draw_AABBs;//!< \b draw_AABBs is of \b Data \b Type: \b int32. It displays the bounding boxes along x-y of the objects
    int32 draw_pairs;//!< \b draw_pairs is of \b Data \b Type: \b int32.
    int32 draw_contact_points;//!< \b draw_contact_points is of \b Data \b Type: \b int32.  It displays the contact points of objects.
    int32 draw_contact_normals;//!< \b draw_contact_normals is of \b Data \b Type: \b int32.  It gives the values of contact forces along the normal
    int32 draw_contact_forces;//!< \b draw_contact_forcesis of \b Data \b Type: \b int32.  It gives the values of contact forces.
    int32 draw_friction_forces;//!< \b draw_friction_forces is of \b Data \b Type: \b int32.  It gives the values of frictional forces.
    int32 draw_COMs;//!< \b draw_COMs is of \b Data \b Type: \b int32.  It displays the center of masses of objects .
    int32 draw_stats;//!< \b draw_stats is of \b Data \b Type: \b int32.  It displays the statistics at the beginning of the simulation.
    int32 draw_profile;//!< \b draw_profile is of \b Data \b Type: \b int32.  It displays the profile of the simulation from the beginning.
    int32 enable_warm_starting;//!< \b enable_warm_starting is of \b Data \b Type: \b int32. Used at beginning of simulation when unimportant events are present.
    int32 enable_continuous;
    int32 enable_sub_stepping;
    int32 pause;//!< \b pause is of \b Data \b Type: \b int32. For pausing the simulation at any point of time.
    int32 single_step;//!< \b single_step is of \b Data \b Type: \b int32.For viewing the simulation step by step.
  };
  //!Sets the title of GUI window apart from doing  other functions like instantiating a particular instance of the world
  
  
  
  struct sim_t
  {
    const char *name;//!< This variabe defines name of the profile
    sim_create_fcn *create_fcn;//!< It is the pointer to the complete file

    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}//!< defines hte simulation with given name and pointer.
  };
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048;  //!< maximum number of contact points 
  //! Has the information about the normal contact at a given point of time.
  struct contact_point_t
  {
    b2Fixture* fixtureA; //!< This is one of the fixtures are the ones which are in contact 
    b2Fixture* fixtureB; //!< This is one of fixtures are the ones which are in contact 
    b2Vec2 normal;//!< Normal vector at the point of contact
    b2Vec2 position;//!< Position of the collision
    b2PointState state;//!< State of the contact point
  };
  /*!This is used for keyboard and mouse interaction of GUI, creates the world and initialises variables this indicates the condition of joints and contacts
   */
  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t();//!< this constructor initialises the world and also introduces the gravity.

    //! Virtual destructors - amazing objects. Why are these necessary?
    virtual ~base_sim_t();//!< It first destroys every object in the current simulation and then destroys the complete simulation recursively.
    
    void set_text_line(int32 line) { m_text_line = line; }//!< It intializes the text displayed on the simulation
    void draw_title(int x, int y, const char *string);//!< Shows the title on the simulation at (x,y)
    //! Most of these void functions do nothing.They are for sake of completeness and avoid warnings
    virtual void step(settings_t* settings);

    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }
	const b2World* get_world(){return m_world;}
    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }

    
    // Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    // Callbacks for derived classes.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  //!How are protected members different from private memebers of a class in C++ ?
  protected:

    //! What are Friend classes?
    friend class contact_listener_t;
    
    b2Body* m_ground_body;//! It is pointer to the body of ground
    b2AABB m_world_AABB;//!< This variable initialises the AABB(Axis Aligned Body Boundaries) in the world
    contact_point_t m_points[k_max_contact_points];//!< Array of contact points
    int32 m_point_count;//!< Keeps count of number of contact points and if they exceed the maximum then it stores the maximum(max_count).

    debug_draw_t m_debug_draw;
    int32 m_text_line;
    b2World* m_world;//!< Pointer to the world

    int32 m_step_count;//!< Keeps count of no of steps
    
    b2Profile m_max_profile;
    b2Profile m_total_profile;
  };
}

#endif
