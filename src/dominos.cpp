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


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /*!  This is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {	
		/*! \section sec Blocks of Graphics
	  
	   */
    //Ground
    /*! \subsection Ground
     * 
	 * \brief It is used to create the ground which we can observe the UI
	 * \li \b b1 is a pointer to a variable of \b Data \b type: \b b2Body* which takes the ground object created from the world object ( \b m_world). 
	 * \li \b shape is a variable of \b Data \b Type: \b b2EdgeShape which is a line between two points (-90.0f,0.0f) and (0.0f,90.0f).It defines the shape for the ground at the bottom using a fixture.
	 * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body.
	 * \li Atlast the body object pointer variable \b b1 is given its shape and density using the CreateFixture member function.
	 */
	
    
    b2Body* b1;  
    {	
	
		
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
     /*! \subsection sec1 Top Horizontal Shelf
      * 
	 * \brief It is used to create the top horizontal shelf which we can observe in the UI.
	 * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.25f and half x-width 6.0f.
	 * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body.
	 * \li \b ground is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference.
	 * \li Atlast the body object pointer variable \b ground is given its shape and density using the CreateFixture member function.
	 */
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    /*! \subsection sec2 Dominos
     * 
	 * \brief It is used to create the vertical tiles on the top horizontal shelf.
	 * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half x-width 0.1f and half y-width 1.0f.
	 * \li \b fd is a variable of \b Data \b Type: \b b2FixtureDef which here gives fixture i.e shape,density,friction to the body.
	 * \li The \b \a  for loop creates those tile objects in different positions.
	 * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and assigns it to be a dyanamic body since it static by default.
	 * \li \b body is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object ( \b m_world) using the definition variable as reference.
	 * \li Atlast the body object pointer variable \b body is given its shape and density using the CreateFixture member function.
	 */

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    
    /*! \subsection sec3 Another Horizontal Shelf
     * 
	 * \brief It is used to create the another horizontal shelf below the Top horizontal shelf which we can observe in the UI.
	 * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.25f and half x-width 7.0f and (-20.0f,20.0f) define the local co-ordinates of the body w.r.t its position co-ordinates.
	 * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body.
	 * \li \b ground is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference.
	 * \li Atlast the body object pointer variable \b ground is given its shape and density using the CreateFixture member function.
	 */
      
    //Another horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f); 										//TO DO THIS
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    
    /*! \subsection sec4  Box and Ball
     * \brief This creates the box and the one of the balls which are present on right top corner of UI .
     * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.25f and half x-width 6.0f.
     * \li \b bd1 is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body.
     * \li \b ground is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference.
     * \li Atlast the body object pointer variable \b ground is given its shape and density using the CreateFixture member function.
     * \li \b bd is a pointer variable of \b Data \b Type: \b b2BodyDef* which is a definition for a body, here it has the initial position of the body and asigns it to be a dyannamic body.
     * \li \b bs1, \b bs2 , \b bs3 are variables of \b Data \b Type: \b b2PolygonShape which gives the objects their respective box shapes.
     * \li \b fd1, \b fd2 , \b fd3 are pointer variables of \b Data \b Type: \b b2FixtureDef* which assign density,friction,shapes (using the respective previous three variables) and restitution of three respective variables.
     *  \li \b box is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable \b bd as reference.
     * \li Now the box variable uses the three fixtures and create the Box.
     * 
     * \li \b sbody is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable \b bd as reference.
     * \li \b circle is a variable of \b Data \b Type: \b b2CircleShape which gives the object a sahpe of circlr and has the radius of the circle stored.
     * \li \b  ballfd is a variable of \b data \b Type: \b b2FixtureDef  which is  a fixture which assigns shape,density,friction and restitution whwn attached to the b2body object.
     * \li \b ballbd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and assign th body typt o be dynamic body.
     * \li Atlast the sbody is attached the fixture.
     */
    
    
    //A Box and a ball
    {
	  b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd1;
      bd1.position.Set(30.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd1);
      ground->CreateFixture(&shape, 0.0f);
      
      //the box
       b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(30.0f, 30.0f);
      
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4,0.2, b2Vec2(0.f,0.5f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.0;
      fd2->restitution = 1.0f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(3.5f,2.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.0;
      fd3->restitution = 1.0f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-3.5f,2.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      
      //ball
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(30.0f, 39.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
  }
	/*! \subsection sec5 Another Ball
     *\brief This creates one of the balls which are present on right top corner of UI .
     * \li \b sbody is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable \b bd as reference.
     * \li \b circle is a variable of \b Data \b Type: \b b2CircleShape which gives the object a shape of circle and has the radius of the circle 1.0 is stored.
     * \li \b  ballfd is a variable of \b data \b Type: \b b2FixtureDef  which is  a fixture which assigns shape,density,friction and restitution whwn attached to the b2body object.
     * \li \b ballbd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and assign th body typt o be dynamic body.
     * \li Atlast the fixture is attached to the sbody.
     */ 
  
		// Another Ball of the diagram
      {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(30.0f, 31.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
      
	}
	
	/*! \subsection sec6 The Pendulum that knocks the Dominos off
	 * 
     *\brief This creates the pendulum and a small rectangular object present below it.
     *\li \b b2 is a pointer to a variable of \b Data \b type: \b b2Body* which takes the ground object created from the world object ( \b m_world). 
     * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 1.5f and half x-width 0.25f.
     * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body.
     * \li Atlast the Createfixture memeber function is used to give shape and density to the body.
     * 
     *\li \b b4 is a pointer to a variable of \b Data \b type: \b b2Body* which takes the ground object created from the world object ( \b m_world). 
     * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.25f and half x-width 0.25f.
     * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and asssigns the body to be a dyanamic body.
     * \li Atlast the Createfixture memeber function is used to give shape and density to the body.
     * 
     * \li jd is variable of \b Data \b Type: b2RevoluteJointDef which is a defintion which when given to the world object creates joint between two bodies at the given postion.
     * \li anchor is a variable of \b Data \b Type: b2Vec2 which is a vector giving the position for the joint.
     * \li Intilaize member function assignds the bodies and their joints to \b jd. And now the world creates the joint taking this revolute joint.
     */
	

    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
    
    /*! \subsection sec7 The Train of Small Spheres
     * 
	 * \brief This is used to create the small spheres on the horizontal shelf below the top horizontal shelf.
	 * \li \b spherebody is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object ( \b m_world) using the definition variable as reference.	 
	 * \li \b circle is a variable of \b Data \b Type: \b b2CircleShape which gives the object a circle shape of radius 0.5f.
	 * \li \b ballfd is a variable of \b Data \b Type: \b b2FixtureDef which here gives fixture i.e shape,density,friction and restitution to the body.
	 * \li The \b \a  for loop creates those sphere objects in different positions.
	 * \li \b ballbd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and assigns it to be a dyanamic body since it static by default.
	 * \li Atlast the body object pointer variable \b spherebody is given its shape and density using the CreateFixture member function.
	 */
      
    //The train of small spheres
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
    
    /*! \subsection sec8 The Pulley System
	 * 
     *\brief This creates the pulley system present at the centre of the screen.
     * \li \b bd is a pointer variable of \b Data \b Type: \b b2BodyDef* which is a definition for a body, here it has the initial position of the body and asigns it to be a dyannamic body and has the fixed the rotation of the body.
     * 
     * \li \b bs1, \b bs2 , \b bs3 are variables of \b Data \b Type: \b b2PolygonShape which gives the objects their respective box shapes and also set their relative position w.r.t the object's position they form.
     * \li \b fd1, \b fd2 , \b fd3 are pointer variables of \b Data \b Type: \b b2FixtureDef* which assign density,friction,shapes (using the respective previous three variables) and restitution of three respective variables.
     * \li \b box1 is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable \b bd as reference.
     * \li Now the box variable uses the three fixtures and create the Box.
     * \li \b box2 is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable \b bd as reference.
     * \li the definition variables \b bd's position is changed and so is the \b fd1's density and then we use them to create and attach to box2 respectively.
     * \li \b myjoint is a pointer to a variable and is of \b Data \b Type: \b b2PulleyJointDef* to which we assign here four position vectors in which two are the centre off mass of the box and the bar and two are fixed.
     * \li The ratio determines the relation between the rates at which the objects on both sides move vertically.
     * \li Atlast we create the object by giving it to the world object.
     * 
     */ 

    //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    
    /*! \subsection sec9 The Revolving Horizontal Platform
     * \brief This creates the revolving horizantal platform which we can observe in the UI.
     * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.2f and half x-width 2.2f.
     * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and assigns it to be a dyanamic body since it static by default.
     * \li \b body is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object ( \b m_world) using the definition variable as reference.
     * \li \b fd is a pointer to a variable of \b Data \b Type: \b b2FixtureDef which is then assigned with shape and density.
     * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.2f and half x-width 2.0f.
     * \li \b bd2 is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the bdy.
     * \li \b body2 is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object ( \b m_world) using the definition variable as reference.
     * \li \b jointDef is variable of \b Data \b Type: \b b2RevoluteJointDef which is used to join \b body , \b body2 , intializing two anchor joints of two bodies and intializing \b false so that two bodies won't collide.s
     * \li Atlast the joint object variable \b jointDef is created using CreateJoint member function.
     * \li \b groundBodyDef is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body.
     * \li \b groundBody is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference.
     * \li \b ajoint is a variable of \b Data \b Type: \b b2DistanceJointDef which is a definition for joining two bodies where distence remain constant between two bodies, here it has two bodies and centers of the two bodies.
     * \li next it is created using create joint member function.
     * \li \b groundshape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half x-width 1.0f and half y-width 1.0f.
     * \li \b fixture is a variable of \b Data \b Type: \b b2FixtureDef which here gives fixture i.e shape,density,friction to the body.
     * \li Atlast fixture is created using \b CreateFixture member function.
     */

    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      //this is our block definition
       b2BodyDef groundBodyDef;
	  groundBodyDef.type = b2_dynamicBody;
	  groundBodyDef.position.Set(13.0f, 1.0f);
	  b2Body* groundBody = (*m_world).CreateBody(&groundBodyDef);
	  b2DistanceJointDef ajoint;
	  ajoint.Initialize(groundBody, body, groundBody->GetWorldCenter(), body->GetWorldCenter());
	  m_world->CreateJoint(&ajoint);
	  b2PolygonShape groundShape;
	  groundShape.SetAsBox(1.0f, 1.0f);
	  b2FixtureDef fixture;
	  fixture.shape = &groundShape;
	  fixture.density = 14.0f;
	  fixture.friction = 0.0f;
	  (*groundBody).CreateFixture(&fixture);
    }
	/*! \subsection sec10 The Heavy sphere on the platform
     *\brief This creates the heavy sphere on the platform of UI .
     * \li \b sbody is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable \b bd as reference.
     * \li \b circle is a variable of \b Data \b Type: \b b2CircleShape which gives the object a shape of circle and has the radius 1.0 of the circle stored.
     * \li \b  ballfd is a variable of \b data \b Type: \b b2FixtureDef  which is  a fixture which assigns shape,density,friction and restitution when attached to the b2body object.
     * \li \b ballbd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and assign th body typt o be dynamic body.
     * \li Atlast the fixture is attached to the sbody.
     */ 
  
    //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
    
    /*! \subsection sec11 The See-Saw System at the Bottom 
     * \brief The triangle wedge:
     * \li \b sbody is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference. 
     * \li \b poly is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a triangle shape set with /b three \b vertices. 
     * \li \b Vertices is a variable of \b Data \b Type: \b b2Vec2 which gives two coordinates for the each vertex.
     * \li \b wedgefd is a variable of \b Data \b Type: \b b2FixtureDef which is then assigned with shape,density,friction and restitution.
     * \li \b wedgebd is a variable of \b Data \b Type: \b b2BodyDef which is set to postion at 30.0f,0.0f.
     * \li Atlast the body object pointer variable \b sbody is given its shape using the CreateFixture member function.
     * \brief The plank on top of the wedge:
     * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.2f and half x-width 15.0f.
     * \li \b bd2 is a variable of \b Data \b Type: \b b2BodyDef which is set to postion at 30.0f,1.5f and it is a moving body.
     * \li \b body is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference.
     * \li \b fd2 is a pointer to a variable of \b Data \b Type: \b b2FixtureDef which is then assigned with shape and density.
     * \li \b jd is variable of \b Data \b Type: \b b2RevoluteJointDef which is used to join \b sbody and \b body at \b anchor.
     * \li \b anchor is the variable name of \b Data \b Type: \b b2Vec2 which gives a coordinates for anchor.
     * \li Atlast the joint object variable \b jd is created using CreateJoint member function.
     * \brief The light box on the right side of the see-saw:
     * \li \b shape2 is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 2.0f and half x-width 2.0f.
     * \li \b bd3 is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and it is movable.
     * \li \b body3 is a pointer to a variable of \b Data \b type: \b b2Body* which takes the ground object created from the world object ( \b m_world).
     * \li \b fd3 is a pointer to a variable of \b Data \b Type: \b b2FixtureDef which is then assigned with shape and density.
     * Atlast the body object pointer variable \b body3 is given its shape using the CreateFixture member function.
     */


    //The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
    
     /*! \subsection sec12 The Falling Wall
      * 
	 * \brief It is used to create the block which is like wall in ground which we can observe in the UI.
	 * \li \b shape is a variable of \b Data \b Type: \b b2PolygonShape which gives the object a box shape of half y-width 0.25f and half x-width 6.0f.
	 * \li \b bd is a variable of \b Data \b Type: \b b2BodyDef which is a definition for a body, here it has the initial position of the body and \b type which makes it moving.
	 * \li \b ground is a pointer to a variable of \b Data \b Type: \b b2Body* which takes the ground object created from the world object( \b m_world) using the definition variable as reference.
	 * \li Atlast the body object pointer variable \b ground is given its shape and density using the CreateFixture member function.
	 */
	 //The Falling Wall
   	{
		b2PolygonShape shape;
      shape.SetAsBox(0.25f, 6.0f);
      b2BodyDef bd;
	  bd.type=b2_dynamicBody;
      bd.position.Set(-38.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 10.0f);
	}
  }
  
 

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
