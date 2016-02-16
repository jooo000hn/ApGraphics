#pragma once

#ifndef __GLEW_H__
	#include <GL/glew.h>
#endif // !__GLEW_H__

#ifndef _STRING_
	#include <string>
#endif // !_STRING_

#ifndef _FSTREAM_
	#include <fstream>
#endif // !_FSTREAM_

#include "../../../../maths/Maths.h"

namespace apanoo {

	// hierarchy
	struct md5_joint_info_t
	{
		std::string name;
		int parentID;
		int flags;
		int startIdx;
	};

	// bounds 存储立方体对角两点
	struct md5_bound_t
	{
		Vector3 min;
		Vector3 max;
	};

	// base frame
	struct md5_base_frame_t
	{
		Vector3 position;
		Quaternion orientation;
	};

	// frames
	struct md5_frame_data_t
	{
		int frameID;
		float* data;
	};

	// skeleton
	struct md5_skeleton_joint_t
	{
		int parentID;
		Vector3 position;
		Quaternion orientation;
	};

	struct md5_frame_skeleton_t
	{
		md5_skeleton_joint_t* joints;
	};

	class MD5Animation
	{
	public:
		MD5Animation();
		~MD5Animation();

		bool init(const char* filename);
		void shutDown();
		void update(float dt);
		inline Matrix4* getAnimationMatrix() { return m_AnimationMatrices; }

	private:
		bool loadAnimation(const char* filename);
		void shutDownAnimation();
		void buildFrameSkeletons(md5_frame_skeleton_t* skeleton,
								 md5_joint_info_t* jointInfoArray,
								 md5_base_frame_t* baseFrameArray,
								 md5_frame_data_t* frameDataArray);
		void interpolateSkeletons(md5_frame_skeleton_t*, md5_frame_skeleton_t*, float);

	private:
		int m_MD5Version;
		int m_NumFrames;
		int m_NumJoints;
		int m_FrameRate;
		int m_NumAnimationComponents;

		float m_FrameDuration;
		float m_AnimationDuration;
		float m_AnimationTime;

		md5_joint_info_t* m_JointInfoArray;
		md5_bound_t* m_BoundArray;
		md5_base_frame_t* m_BaseFrameArray;
		md5_frame_data_t* m_FrameDataArray;

		md5_frame_skeleton_t* m_FrameSkeletonArray;
		Matrix4* m_AnimationMatrices;
	};
}