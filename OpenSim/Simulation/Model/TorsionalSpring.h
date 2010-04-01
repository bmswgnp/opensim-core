#ifndef _TorsionalSpring_h_
#define _TorsionalSpring_h_
// TorsionalSpring.h
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


//=============================================================================
// INCLUDES
//=============================================================================
#include <OpenSim/Simulation/Manager/Manager.h>
#include <OpenSim/Common/FunctionSet.h>
#include <OpenSim/Common/VectorFunction.h>
#include "CustomForce.h"


//=============================================================================
//=============================================================================
/**
 * A custom force used for applying external torques during a
 * simulation.  The magnitude of the torque is calculated based on the 
 * deviation in angular position and velocity of the body from a prescribed
 * position and velocity.
 *
 * @author Ajay Seth, Frank C. Anderson, Saryn Goldberg
 * @version 1.0
 */
namespace OpenSim { 

class Model;
class Body;

class OSIMSIMULATION_API TorsionalSpring : public CustomForce 
{
//=============================================================================
// DATA
//=============================================================================
protected:
	/** Vector function containing target orientation of the body. */
	VectorFunction *_targetPosition;
	/** Vector function containing target angular velocity of the body. */
	VectorFunction *_targetVelocity;
	/** Function containing values for the time-dependent torque scaling factor. */
	Function *_scaleFunction;
	/** Scale factor that pre-multiplies the applied torque */
	double _scaleFactor;
	/** Stiffness. */
	SimTK::Vec3 _k;
	/** Damping. */
	SimTK::Vec3 _b;
	/** If the magnitude of the torque is below this threshold, no torque
	is applied. */
	double _threshold;
	const Body &_body;

	/** On, off flag. */
	bool _on;
	/** Start time for the force. */
	double _startTime;
	/** End time for the force. */
	double _endTime;

//=============================================================================
// METHODS
//=============================================================================
public:
	TorsionalSpring(const Body &aBody, double startTime, double endTime);
	virtual ~TorsionalSpring();
private:
	void setNull();

public:
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	void setTargetPosition(VectorFunction* aPosFunction);
	VectorFunction* getTargetPosition() const;
	void setTargetVelocity(VectorFunction* aVelFunction);
	VectorFunction* getTargetVelocity() const;
	void setScaleFunction(Function* _scaleFunction);
	Function* getScaleFunction() const;
	void setScaleFactor(double aScaleFactor);
	double getScaleFactor();
	void setKValue(const SimTK::Vec3& aK);
	void getKValue(SimTK::Vec3& aK);
	void setBValue(const SimTK::Vec3& aB);
	void getBValue(SimTK::Vec3& aB);
	void setThreshold(double aThreshold);
	double getThreshold() const;
    void setOn( bool on_off ) { _on = on_off; }
    bool getOn() const { return _on; }

	//--------------------------------------------------------------------------
	// UTILITY
	//--------------------------------------------------------------------------
	void computeTargetFunctions(SimTK::State &s, const Storage &aQStore,const Storage &aUStore);
	
	//--------------------------------------------------------------------------
	// Force
	//--------------------------------------------------------------------------
	virtual void computeForce(const SimTK::State& state, 
							  SimTK::Vector_<SimTK::SpatialVec>& bodyForces, 
							  SimTK::Vector& generalizedForces) const;

//=============================================================================
};	// END of class TorsionalSpring

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __TorsionalSpring_h__