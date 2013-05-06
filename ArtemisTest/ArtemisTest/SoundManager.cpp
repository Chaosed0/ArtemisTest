
#include "SoundManager.h"

std::map<std::string, sf::SoundBuffer> SoundManager::soundBuffers;
std::list<std::shared_ptr<sf::Sound>> SoundManager::playingSounds;

std::shared_ptr<sf::Sound> SoundManager::PlaySound(const std::string& path, bool loop)
{
	playingSounds.push_back(std::shared_ptr<sf::Sound>(new sf::Sound(GetSoundBuffer(path))));
	playingSounds.back()->setLoop(loop);
	playingSounds.back()->play();

	for(std::list<std::shared_ptr<sf::Sound>>::iterator iter = playingSounds.begin();
			iter != playingSounds.end(); iter++) {
		if((*iter)->getStatus() == sf::Sound::Stopped) {
			iter = playingSounds.erase(iter);
		}
	}

	return playingSounds.back();
}

void SoundManager::PrecacheSound(const std::string& path)
{
	GetSoundBuffer(path);
}
	
sf::SoundBuffer& SoundManager::GetSoundBuffer(const std::string& path)
{
	soundBufferIterator iter = soundBuffers.find(path);
	if(iter == soundBuffers.end()) {
		soundBuffers[path] = sf::SoundBuffer();
		soundBuffers[path].loadFromFile(path);
		return soundBuffers[path];
	} else {
		return iter->second;
	}
}
