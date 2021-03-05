#include "SoundEffect.h"

SoundEffect::SoundEffect(std::string path)
{
	m_path = path;
}

SoundEffect::~SoundEffect()
{
	m_sound = nullptr;
}

void SoundEffect::Play()
{
		m_sound = Mix_LoadWAV(m_path.c_str());
		if (m_sound == nullptr)
		{
			std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
		}
		else
		{
			Mix_PlayChannel(-1, m_sound, 0);
		}

}
