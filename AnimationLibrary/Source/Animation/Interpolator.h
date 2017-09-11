#ifndef _INTERPOLATOR_H_
#define _INTERPOLATOR_H_
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>

#include "Animation/Animation.h"
#include "Math/matrix4.h"

#undef min
#undef max

template < typename T >
class Interpolator
{
public:

	Interpolator();
	virtual ~Interpolator();

	void SetAnimation(const Animation< T >* animation);
	const Animation< T >* GetAnimation() const;

	void AddTime(float time);
	void SetTime(float time);
	float GetTime() const;

	virtual void Process();

	const std::vector< T >& GetPose() const;

protected:

	void ProcessKeyframes(const std::vector< typename Animation< T >::KeyFrame >& key_frames);

	const Animation< T >* animation;
	float current_time;

	std::vector< T > pose;

	//stuff i'm adding
	typename Animation<T>::KeyFrame next;
	typename Animation<T>::KeyFrame curr;

};

template < typename T >
Interpolator< T >::Interpolator()
{
	animation = 0;
	current_time = 0.0f;
}

template < typename T >
Interpolator< T >::~Interpolator()
{
}

template < typename T >
void Interpolator< T >::SetAnimation(const Animation< T >* animation)
{
	// TODO
	//setting an internal variable to the animation data

	this->animation = animation;

	current_time = 0;
}

template < typename T >
const Animation< T >* Interpolator< T >::GetAnimation() const
{
	return animation;
}

template < typename T >
void Interpolator< T >::AddTime(float time)
{
	SetTime(current_time + time);
}

template < typename T >
void Interpolator< T >::SetTime(float time)
{
	// TODO
	//time change = animation change

	if (animation != NULL)
	{
		//check to see if the passed in time is more than the max animation time or less than the minimum if the animation is in reverse. If so, reset the time
		current_time = time;
		if (current_time > animation->GetDuration())
			current_time = 0;
		//this might be wrong
		else if (current_time < 0)
			current_time = animation->GetDuration();
		//this might be wrong
	}
	else
		current_time = 0;
}

template < typename T >
float Interpolator< T >::GetTime() const
{
	return current_time;
}

template < typename T >
void Interpolator< T >::Process()
{
	if (animation == 0)
	{
		pose.clear();
		return;
	}

	ProcessKeyframes(animation->GetKeyFrames());
}

template < typename T >
const std::vector<T>& Interpolator< T >::GetPose() const
{
	return pose;
}

template < typename T >
void Interpolator< T >::ProcessKeyframes(const std::vector< typename Animation< T >::KeyFrame >& key_frames)
{
	// TODO: Fill out the "pose" vector.  You are responsible for sizing it appropriately.
	//  "key_frames" contains an array of poses.
	//  "current_time" contains our current time.
	pose.resize(key_frames.size());


	for (unsigned int i = 0; i < key_frames.size(); ++i)
	{
		if (key_frames[i].time > current_time)
		{
			if (i == 0)
			{
				curr.nodes = key_frames[key_frames.size() - 1].nodes;
				curr.time = 0;
			}
			else
			{
				curr = key_frames[i - 1];
			}

			next = key_frames[i];
			break;
		}
	}


	for (unsigned int j = 0; j < next.nodes.size(); ++j)
	{
		float check = (current_time - curr.time) / (next.time - curr.time);

		vec3f temp = curr.nodes[j] + (next.nodes[j] - curr.nodes[j])*check;

		next.nodes[j] = temp;
	}

	pose = next.nodes;
}

#endif // _INTERPOLATOR_H_