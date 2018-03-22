#include "../stdafx.h"
#include "ConverterAnimationController.h"
#include "ConverterAnimation.h"

ConverterAnimationController::ConverterAnimationController()
	: currentAnimation(NULL), prevAnimation(NULL)
	, currentKeyFrame(0), nextKeyFrame(0), keyFrameFactor(0.0f), frameTimer(0.0f)
	, isLoop(false)
{
	useQuaternionKeyFrames = true;

	animationMode = AnimationMode::Stop;
}

ConverterAnimationController::~ConverterAnimationController()
{
	for each(Pair temp in animations)
		SAFE_DELETE(temp.second);
	
	currentAnimation = NULL;
}

/****************************************************************************************************
 @brief
 animations에 ConverterAnimation을 Animation 이름 별로 추가
****************************************************************************************************/
void ConverterAnimationController::AddAnimation(ConverterAnimation * animation)
{
	bool isExist = false;
	for (size_t i = 0; i < animations.size(); i++)
	{
		// 중복 확인
		if (animations[i].first == animation->GetName())
		{
			isExist = true;
			
			break;
		}
	}
	assert(isExist == false);

	animations.push_back(Pair(animation->GetName(), animation));
}

ConverterAnimation * ConverterAnimationController::GetCurrentAnimation()
{
	if(currentAnimation != NULL)
		return currentAnimation;

	return NULL;
}

/****************************************************************************************************
 @brief
 Animation의 이름으로 현재 Animation을 설정
****************************************************************************************************/
void ConverterAnimationController::SetCurrentAnimation(wstring animationName)
{
	UINT count = -1;
	for (size_t i = 0; i < animations.size(); i++)
	{
		if (animations[i].first == animationName)
		{
			count = i;
			break;
		}
	}
	
	if (count != -1)
	{
		if (currentAnimation == animations[count].second)
			return;

		// 현재 애니메이션 교체, 이전 애니메이션 저장
		prevAnimation = currentAnimation;
		currentAnimation = animations[count].second;
	}
	else
		return;

	// 현재 Animation이 바뀌면 Animation 실행 중지
	Stop();
}

/****************************************************************************************************
 @brief
 Animation의 Index로 현재 Animation을 설정
****************************************************************************************************/
void ConverterAnimationController::SetCurrentAnimation(int index)
{
	if( index < 0 || index >= (int)animations.size() )
		currentAnimation = NULL;
	else
	{
		prevAnimation = currentAnimation;
		currentAnimation = animations[index].second;
	}
	
	Stop();
}

UINT ConverterAnimationController::GetAnimationCount()
{
	return animations.size();
}

ConverterAnimation * ConverterAnimationController::GetAnimation(int index)
{
	if( index < 0 || index >= (int)animations.size() )
		return NULL;
	else
		return animations[index].second;
}

ConverterAnimation * ConverterAnimationController::GetAnimation(wstring animName)
{
	UINT count = -1;
	for (size_t i = 0; i < animations.size(); i++)
	{
		if (animations[i].first == animName)
		{
			count = i;
			break;
		}
	}

	if (count != -1)
	{
		return animations[count].second;
	}
	else
		return NULL;
}

void ConverterAnimationController::Play()
{
	currentAnimation->SetIsEnd(false);
	animationMode = AnimationMode::Play;
}

void ConverterAnimationController::Pause()
{
	animationMode = AnimationMode::Pause;
}

void ConverterAnimationController::Stop()
{
	animationMode = AnimationMode::Stop;
	frameTimer = 0.0f;

	SetCurrentKeyFrame(0);
}

/****************************************************************************************************
 @brief
 현재 KeyFrame, 다음 KeyFrame을 설정
****************************************************************************************************/
void ConverterAnimationController::SetCurrentKeyFrame(int keyFrame)
{
	currentKeyFrame = (keyFrame) % currentAnimation->GetKeyFrameCount();
	nextKeyFrame = (currentKeyFrame + 1) % currentAnimation->GetKeyFrameCount();
	
	keyFrameFactor = 0.0f;
}
