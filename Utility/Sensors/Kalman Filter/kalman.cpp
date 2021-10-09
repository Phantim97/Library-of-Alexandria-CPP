#include <iostream>
/*=============================================================================
*
* State Object
*
=============================================================================*/
class State
{
private:
	float m_lat; float m_long; float m_feet;
	float m_deg; float m_sat; float m_gyx;
	float m_gyy; float m_gyz;

public:
	//Data
	float m_acx; float m_acy; float m_acz;
	float m_mph; float m_deltaT;

	//Calculated data
	float m_velocity; float m_kalGain; float m_estimateVel;
	float m_errEst;

	State();
	~State();
	State& operator=(State &&other);
	void dataSet(float sensorData[13]); // Arduino data -> object
	void printDataSet();
	float getSat();
};

State::State()
{
	this->m_lat = 0; this->m_long = 0; this->m_feet = 0;
	this->m_deg = 0; this->m_mph = 0; this->m_sat = 0;
	this->m_acx = 0; this->m_acy = 0; this->m_acz = 0;
	this->m_gyx = 0; this->m_gyy = 0; this->m_gyz = 0;
	this->m_kalGain = .5; this->m_deltaT = 0; this->m_estimateVel = 0;
	this->m_errEst = .4;
}

State::~State()
{
	printf("Resource Cleared\n");
	delete this;
}

void State::dataSet(float sensorData[13])
{
	this->m_lat = sensorData[0]; this->m_long = sensorData[1]; this->m_feet = sensorData[2];
	this->m_deg = sensorData[3]; this->m_mph = sensorData[4]; this->m_sat = sensorData[5];
	this->m_acx = sensorData[6]; this->m_acy = sensorData[7]; this->m_acz = sensorData[8];
	this->m_gyx = sensorData[9]; this->m_gyy = sensorData[10]; this->m_gyz = sensorData[11];
	this->m_deltaT = sensorData[12];
}



State& State::operator=(State &&other)
{
	m_acx = other.m_acx; m_acy = other.m_acy; m_acz = other.m_acz;
	m_deltaT = other.m_deltaT; m_velocity = other.m_velocity;
	m_estimateVel = other.m_estimateVel; m_mph = other.m_mph;
	m_errEst = other.m_errEst;
	return *this;
}

void State::printDataSet()
{
	std::cout << "GPS:\n";
	std::cout << "LAT: " << this->m_lat << " | LONG: " << this->m_long << " | DEG: " << this->m_deg << " | MPH: " << this->m_mph << " | SAT: " << this->m_sat << '\n';
	std::cout << "MPU:\n";
	std::cout << "ACX: " << this->m_acx << " | ACY: " << this->m_acy << " | ACZ: " << this->m_acx << " | GYX: " << this->m_gyx << " | GYY: " << this->m_gyy << " | GYZ: " << this->m_gyz << '\n';
}

float State::getSat()
{
	return this->m_sat;
}

/*=============================================================================
=============================================================================*/


/*=============================================================================
*
* KALMAN FILTER
*
=============================================================================*/


const float g_measure_err = .04f; // global for measurement error

namespace Kalman
{
	void calcGain(State &k1);
	void calcCurrentEstimate(State &k0, State &k1);
	void calcErrorNewEstimate(State &k0, State &k1);
}

void Kalman::calcGain(State &k1)
{
	/*
		KG = E(est)/(E(est)+E(mea))
	*/
	k1.m_kalGain = k1.m_errEst / (k1.m_errEst + g_measure_err);

}

void Kalman::calcCurrentEstimate(State &k0, State &k1)
{
	/*
		EST(t) = EST(t-1) + KG[MEA - EST(t-1)]
	*/
	k1.m_estimateVel = k0.m_estimateVel + (k1.m_kalGain * (k1.m_mph - k0.m_estimateVel));
}

void Kalman::calcErrorNewEstimate(State &k0, State &k1)
{
	/*
		E(EST(t)) = (E(MEA)E(EST(t)))/(E(MEA)+E(EST(t-1))
		= [1-KG](E(EST(t-1)))
	*/
	k1.m_errEst = (1 - k1.m_kalGain) * k0.m_errEst;
}

/*=============================================================================
=============================================================================*/

struct Position
{
	float latitude;
	float longitude;
};

void calcPosition(Position &pre, Position &p, float *vel)
{
	//Calculate new position and update Position object
}

void func()
{
	float q0, q1, q2, q3;
	float R[3][3];
	R[0][0] = 1 - (2 * ((q2 * q2)+(q3 * q3))); R[0][1] = 2 * ((q1 * q2) - (q0 * q3));		R[0][2] = 2 * ((q0 * q2) + (q1 * q3));
	R[1][0] = 2 * ((q1 * q2) + (q0 * q3));     R[1][1] = 1 - (2 * ((q1 * q1) + (q3 * q3))); R[1][2] = 2 * ((q2 * q3) + (q0 * q1));
	R[2][0] = 2 * ((q1 * q3) + (q0 * q2));	   R[2][1] = 2 * ((q0 *q1) + (q2 * q3));        R[2][2] = 1 - (2 * ((q1 * q1) + (q2 * q2)));
}
#define PI 3.14159

void ypr()
{
	float q0, q1, q2, q3;
	double roll = atan2(2 * ((q0*q1) + (q2*q3)), 1 - (2*((q1*q1)+(q2*q2))));
	double pitch;
	double sinp = 2 * ((q0*q2) - (q3*q1));
	if (fabs(sinp) >= 1)
	{
		pitch = copysign(PI / 2, sinp); // use 90 deg if out of range
	}
	else
	{
		pitch = asin(sinp);
	}
	double yaw = atan2(2 * ((q0*q3) + (q1*q2)), 1 - (2 * ((q2 * q2) + (q3*q3))));
}

/*
	Function: JNI Main
	Params: sensor data, old GPS, new GPS, firstRun bool, Kalman features (State 0/1) in forms of arrays
*/
int main()
{
	bool firstRun = true; //obtained from param
	State k0;
	State k1;
	Position prev;
	Position pos;
	if (firstRun)
	{
		//store sensor data into k0 and wait for next GPS
		firstRun = false;
	}
	else
	{
		//set current state to be previous
		k0 = std::move(k1);
		//store sensor data into k1
		Kalman::calcGain(k1);
		Kalman::calcCurrentEstimate(k0, k1);
		Kalman::calcErrorNewEstimate(k0, k1);

		//Use estimated velocity to calculate position
		calcPosition(prev, pos, &k1.m_estimateVel);
	}

	std::cin.get();
	return 0;
}
