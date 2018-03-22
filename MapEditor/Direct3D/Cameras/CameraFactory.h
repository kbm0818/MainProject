#pragma once

struct CameraDesc;
class CameraFactory
{
public:
	template<typename T>
	static T* Create()
	{
		T* obj = new T();
		cameras.push_back(obj);

		return obj;
	}

	static void Delete(Camera* camera)
	{
		int number = -1; 
		for (size_t i = 0; i < cameras.size(); i++)
		{
			if (cameras[i] == camera)
			{
				number = (int)i;
				break;
			}

			if (number > -1)
			{
				SAFE_DELETE(cameras[i]);
				cameras.erase(cameras.begin() + number);
			}
		}
	}

private:
	static vector<Camera *> cameras;
};