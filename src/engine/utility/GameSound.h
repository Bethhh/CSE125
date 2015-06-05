#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#define SFML_STATIC
#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
#pragma comment(lib, "winmm.lib") // SO weird I need this for music

#define SOUND_OUCH_NUM 10
const bool SOUND_ENABLE = true;

class GameSound 
{
public:
	static sf::Sound	*menumove,
						*menuconfirm,
						*menuback,
						*blobmove,
						*nom,
						*regburp,
						*bigburp,
						*jump,
						*spaceship,
						*loadingnow,
						*spaceship_loading,
						*ouch_arr[SOUND_OUCH_NUM]
						;

	static sf::Music	*menubgm,
						*menubgm2,
						*ingamebgm,
						*ingamebgm2,
						*loadingloop;

	static void init();

	static void playOuch();
	static void playLoading();
	static void stopLoading();

private:
	//music doesn't need buffer
	static sf::SoundBuffer	*menumove_buf, 
							*menuconfirm_buf,
							*menuback_buf,
							*blobmove_buf,
							*nom_buf, 
							*regburp_buf, 
							*bigburp_buf, 
							*jump_buf,
							*spaceship_buf,
							*loadingnow_buf,
							*spaceship_loading_buf,
							*ouch_buf_arr[SOUND_OUCH_NUM]
							;

	static void loadSound(sf::Sound *sound, sf::SoundBuffer *buffer, std::string path);
	static void loadSoundColl(sf::Sound *sound[], sf::SoundBuffer *buffer[], std::string path, int size);
	static void loadMusic(sf::Music *music, std::string path);
	
};

#endif