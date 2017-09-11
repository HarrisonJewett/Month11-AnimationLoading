#include "VertLoader.h"

#include <fstream>
#include <vector>

#include "Animation/Animation.h"
#include "Math/vec3.h"

using namespace std;


bool VertLoader::Load( const std::string& file_name, Animation< vec3f >& animation )
{
	int numberOfKeyFrames = 0;
	int nodeCount = 0;

    // TODO

	vector<Animation<vec3f>::KeyFrame> & frames = animation.GetKeyFrames();

	ifstream file(file_name, ios::binary);

	file.read((char*)&numberOfKeyFrames, 4);

	//float* keyFrameTime = new float[numberOfKeyFrames];
	vec3f* nodeData = new vec3f[numberOfKeyFrames];

	frames.resize(numberOfKeyFrames);
	
	for (int i = 0; i < numberOfKeyFrames; ++i)
	{
		//file.read((char*)&keyFrameTime[i], 4);
		file.read((char*)&frames[i].time, 4);
		//file.read((char*)&nodeCount[i], 4);
		file.read((char*)&nodeCount, 4);
		frames[i].nodes.resize(nodeCount);

		for (unsigned int j = 0; j < frames[i].nodes.size(); ++j)
		{
			//file.read((char*)&nodeData[j].x, 4); //x
			//file.read((char*)&nodeData[j].y, 4); //y
			//file.read((char*)&nodeData[j].z, 4); //z
			file.read((char*)&frames[i].nodes[j].x, 4);
			file.read((char*)&frames[i].nodes[j].y, 4);
			file.read((char*)&frames[i].nodes[j].z, 4);
		}
	}
    return true;
}