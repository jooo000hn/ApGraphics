#include "MD5Anim.h"
#include "helper.h"

namespace apanoo {

	MD5Animation::MD5Animation()
	{
		m_JointInfoArray = NULL;
		m_BoundArray = NULL;
		m_BaseFrameArray = NULL;
		m_FrameDataArray = NULL;

		m_FrameSkeletonArray = NULL;
		m_AnimationMatrices = NULL;
	}

	MD5Animation::~MD5Animation()
	{

	}

	bool MD5Animation::init(const char* filename)
	{
		if (!loadAnimation(filename))
		{
			return false;
		}
		shutDownAnimation();
		return true;
	}

	void MD5Animation::shutDown()
	{
		if (m_FrameSkeletonArray)
		{
			for (int i = 0;i < m_NumFrames;i++)
			{
				delete[] m_FrameSkeletonArray[i].joints;
				m_FrameSkeletonArray[i].joints = NULL;
			}
			delete[] m_FrameSkeletonArray;
			m_FrameSkeletonArray = NULL;
		}
		if (m_AnimationMatrices)
		{
			delete[] m_AnimationMatrices;
			m_AnimationMatrices = NULL;
		}
	}

	void MD5Animation::update(float dt)
	{
		m_AnimationTime += dt;
		if (m_AnimationTime > m_AnimationDuration)
		{
			m_AnimationTime = 0.0f;
		}
		// frame 5
		// 5.5
		// frame 6
		float curframe = m_AnimationTime * float(m_FrameRate);
		int frame0 = (int)floorf(curframe);
		int frame1 = frame0 + 1;

		if (frame0 == m_NumFrames - 1)
		{
			frame0 = 0;
		}
		float alpha = curframe - (float)frame0;

		interpolateSkeletons(&m_FrameSkeletonArray[frame0], &m_FrameSkeletonArray[frame1], alpha);
	}

	bool MD5Animation::loadAnimation(const char* filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			return false;
		}

		// 计算文件长度
		int initpos = (int)file.tellg();
		file.seekg(0, std::ios::end);
		int filelength = (int)file.tellg();
		file.seekg(initpos);

		std::string param, junk;
		file >> param;

		while (!file.eof())
		{
			if (param == "MD5Version")
			{
				file >> m_MD5Version;
				if (!m_MD5Version)
				{
					return false;
				}
				std::cout << "MD5Version: " << m_MD5Version << std::endl;
			} else if (param == "commandline")
			{
				file.ignore(filelength, '\n');
			} else if (param == "numFrames")
			{
				file >> m_NumFrames;
				m_BoundArray = new md5_bound_t[m_NumFrames];
				if (!m_BoundArray)
				{
					return false;
				}

				m_FrameDataArray = new md5_frame_data_t[m_NumFrames];
				if (!m_FrameDataArray)
				{
					return false;
				}

				m_FrameSkeletonArray = new md5_frame_skeleton_t[m_NumFrames];
				if (!m_FrameSkeletonArray)
				{
					return false;
				}

				std::cout << "numFrames: " << m_NumFrames << std::endl;
			} else if (param == "")
			{
				file >> m_NumJoints;
				m_JointInfoArray = new md5_joint_info_t[m_NumJoints];
				if (!m_JointInfoArray)
				{
					return false;
				}

				m_BaseFrameArray = new md5_base_frame_t[m_NumJoints];
				if (!m_BaseFrameArray)
				{
					return false;
				}

				m_AnimationMatrices = new Matrix4[m_NumJoints];
				if (!m_AnimationMatrices)
				{
					return false;
				}

				std::cout << "numJoints: " << m_NumJoints << std::endl;
			} else if (param == "frameRate")
			{
				file >> m_FrameRate;
				std::cout << "frameRate: " << m_FrameRate << std::endl;
			} else if (param == "numAnimatedComponents")
			{
				file >> m_NumAnimationComponents;
				std::cout << "numAnimatedComponents: " << m_NumAnimationComponents << std::endl;
			} else if (param == "hierarchy")
			{
				file >> junk; // {
				for (int i = 0;i < m_NumJoints;i++)
				{
					md5_joint_info_t joint;
					file >> joint.name >> joint.parentID >> joint.flags >> joint.startIdx;
					file.ignore(filelength, '\n');

					removeQuotes(joint.name);
					m_JointInfoArray[i] = joint;
				}
				file >> junk; // }
			} else if (param == "bounds")
			{
				file >> junk; // {
				for (int i = 0;i < m_NumFrames;i++)
				{
					md5_bound_t bound;
					file >> junk;
					file >> bound.min[0] >> bound.min[1] >> bound.min[2];
					file >> junk >> junk; // )(
					file >> bound.max[0] >> bound.max[1] >> bound.max[2];
					file >> junk; // )

					m_BoundArray[i] = bound;

				}
				file >> junk; // }
			} else if (param == "baseframe")
			{
				file >> junk; // {
				for (int i = 0;i < m_NumJoints;i++)
				{
					md5_base_frame_t joint;
					file >> junk; // (
					file >> joint.position[0] >> joint.position[1] >> joint.position[2];
					file >> junk >> junk; // )(
					file >> joint.orientation[0] >> joint.orientation[1] >> joint.orientation[2];
					file >> junk; // )

					m_BaseFrameArray[i] = joint;
				}
				file >> junk; // }
			} else if (param == "frame")
			{
				md5_frame_data_t frame;
				file >> frame.frameID >> junk; // {

				frame.data = new float[m_NumAnimationComponents];
				if (!frame.data)
				{
					return false;
				}

				m_FrameSkeletonArray[frame.frameID].joints = new md5_skeleton_joint_t[m_NumJoints];
				if (!m_FrameSkeletonArray[frame.frameID].joints)
				{
					return false;
				}

				for (int i = 0;i < m_NumAnimationComponents;i++)
				{
					file >> frame.data[i];
				}

				m_FrameDataArray[frame.frameID] = frame;
				buildFrameSkeletons(&m_FrameSkeletonArray[frame.frameID], 
									 m_JointInfoArray, 
									 m_BaseFrameArray, 
									&frame);

				file >> junk; // }
			}

			file >> param;
		}

		return true;
	}

	void MD5Animation::shutDownAnimation()
	{
		if (m_JointInfoArray)
		{
			delete[] m_JointInfoArray;
			m_JointInfoArray = NULL;
		}

		if (m_BoundArray)
		{
			delete[] m_BoundArray;
			m_BoundArray = NULL;
		}

		if (m_BaseFrameArray)
		{
			delete[] m_BaseFrameArray;
			m_BaseFrameArray = NULL;
		}

		if (m_FrameDataArray)
		{
			for (int i = 0;i < m_NumFrames;i++)
			{
				delete m_FrameDataArray[i].data;
				m_FrameDataArray[i].data = NULL;
			}
			delete[] m_FrameDataArray;
			m_FrameDataArray = NULL;
		}
	}

	void MD5Animation::buildFrameSkeletons(md5_frame_skeleton_t* skeleton, 
										   md5_joint_info_t* jointInfoArray, 
										   md5_base_frame_t* baseFrameArray,
										   md5_frame_data_t* frameDataArray)
	{
		md5_skeleton_joint_t animjoint;
		for (int i = 0;i < m_NumJoints;i++)
		{
			int j = 0;
			md5_joint_info_t& jointinfo = jointInfoArray[i];
			md5_base_frame_t& baseframe = baseFrameArray[i];
			memcpy(&animjoint.position, &baseframe.position, sizeof(Vector3));
			memcpy(&animjoint.orientation, &baseframe.orientation, sizeof(Vector4));

			if (jointinfo.flags & 1)
			{
				animjoint.position[0] = frameDataArray->data[jointinfo.startIdx + j++];
			}
			if (jointinfo.flags & 2)
			{
				animjoint.position[1] = frameDataArray->data[jointinfo.startIdx + j++];
			}
			if (jointinfo.flags & 4)
			{
				animjoint.position[2] = frameDataArray->data[jointinfo.startIdx + j++];
			}

			Vector3 tmp_orientation;
			if (jointinfo.flags & 8)
			{
				tmp_orientation[0] = frameDataArray->data[jointinfo.startIdx + j++];
			}
			if (jointinfo.flags & 16)
			{
				tmp_orientation[1] = frameDataArray->data[jointinfo.startIdx + j++];
			}
			if (jointinfo.flags & 32)
			{
				tmp_orientation[2] = frameDataArray->data[jointinfo.startIdx + j++];
			}

			animjoint.orientation = Quaternion(tmp_orientation.getX(), tmp_orientation.getY(), tmp_orientation.getZ(), computeQuaternionW(tmp_orientation));
			if (animjoint.parentID >= 0)
			{
				md5_skeleton_joint_t& parentjoint = skeleton->joints[animjoint.parentID];
				Vector3 rotpos = animjoint.position.rotate(parentjoint.orientation);

				animjoint.position[0] = parentjoint.position[0] + rotpos[0];
				animjoint.position[1] = parentjoint.position[1] + rotpos[1];
				animjoint.position[2] = parentjoint.position[2] + rotpos[2];

				animjoint.orientation = parentjoint.orientation * animjoint.orientation;
				animjoint.orientation = animjoint.orientation.normalized();

				memcpy(&skeleton->joints[i], &animjoint, sizeof(md5_skeleton_joint_t));
			}
			else {
				memcpy(&skeleton->joints[i], &animjoint, sizeof(md5_skeleton_joint_t));
			}
		}
	}

	void MD5Animation::interpolateSkeletons(md5_frame_skeleton_t* skeleton0, 
											md5_frame_skeleton_t* skeleton1, 
											float alpha)
	{
		Matrix4 finalmatrix, rotation, translation;
		md5_skeleton_joint_t finaljoint;
		for (int i = 0;i < m_NumJoints;i++)
		{
			md5_skeleton_joint_t& joint0 = skeleton0->joints[i];
			md5_skeleton_joint_t& joint1 = skeleton1->joints[i];

			finaljoint.position[0] = (1.0f - alpha) * joint0.position[0] + alpha * joint1.position[0];
			finaljoint.position[1] = (1.0f - alpha) * joint0.position[1] + alpha * joint1.position[1];
			finaljoint.position[2] = (1.0f - alpha) * joint0.position[2] + alpha * joint1.position[2];

			mlSlerp(&finaljoint.orientation, &joint0.orientation, &joint1.orientation, alpha);

			rotation = Matrix4(finaljoint.orientation);
			translation = Matrix4().translationMatrix(finaljoint.position);
			finalmatrix = translation * rotation;

			memcpy(&m_AnimationMatrices[i], &finalmatrix, sizeof(Matrix4));
		}
	}

}