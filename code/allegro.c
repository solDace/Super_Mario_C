/**
 * @file allegro.c
 * @brief Ensemble des fonctions reltives à la library
 * @version 0.1
 * @date 2021-01-10
 */

#include "allegro.h"

init initLib()
{
    init set;
    set.success = 0;
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        set.success = 1;
    }

    if (!al_install_keyboard())
        printf("couldn't initialize keyboard\n");

    set.timer = al_create_timer(1.0 / REFRESH_RATE);

    if (!set.timer)
        printf("couldn't initialize timer\n");

    set.queue = al_create_event_queue();

    if (!set.queue)
        printf("couldn't initialize queue\n");

    //n�cessaire pour laod et save bitmap
    if (!al_init_image_addon())
        printf("al_init_image_addon()");

    al_set_new_display_refresh_rate(REFRESH_RATE);
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    set.disp = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!set.disp)
        printf("couldn't initialize display\n");

    al_init_font_addon();
    al_init_ttf_addon();
    if (!al_init_ttf_addon())
        printf("al_init_ttf_addon()");

    set.font = al_load_ttf_font("./AlgoS4/resources/fonts/gameplay.ttf", 24, 0);
    if (!set.font)
        printf("couldn't initialize font\n");

    al_init_primitives_addon();
    if (!al_init_primitives_addon())
        printf("al_primitives_addon()");

    if (!al_install_mouse())
        printf("al_install_mouse()");

    al_register_event_source(set.queue, al_get_keyboard_event_source());
    al_register_event_source(set.queue, al_get_display_event_source(set.disp));
    al_register_event_source(set.queue, al_get_timer_event_source(set.timer));

    return set;
}

sound initSound()
{
    sound set;

    al_install_audio();
    al_init_acodec_addon();
    if (!al_init_acodec_addon())
        printf("al_init_acodec_addon()");

    set.music_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    set.sound_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    set.master_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    set.voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    al_attach_mixer_to_voice(set.master_mixer, set.voice);
    al_reserve_samples(1);

    set.songInstance = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/overworld.wav"));

    if (!set.songInstance)
        printf("couldn't initialize song instance\n");
    set.die = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/die.wav"));

    set.star = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/star.wav"));
    if (!set.star)
        printf("couldn't initialize song star\n");

    set.pause = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/Pause.wav"));
    if (!set.pause)
        printf("couldn't initialize song pause\n");

    set.click_pause = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_pause.wav"));
    if (!set.click_pause)
        printf("couldn't initialize song click_pause\n");

    if (!set.die)
        printf("couldn't initialize song die\n");

    set.jump = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_jump-small.wav"));
    if (!set.jump)
        printf("couldn't initialize song jump\n");
    set.gameOver = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_gameover.wav"));
    if (!set.gameOver)
        printf("couldn't initialize song gameover\n");

    set.breakBlock = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_breakblock.wav"));
    if (!set.breakBlock)
        printf("couldn't initialize song breakblock\n");

    set.bump = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_bump.wav"));
    if (!set.bump)
        printf("couldn't initialize song bump\n");

    set.stomp = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_stomp.wav"));
    if (!set.stomp)
        printf("couldn't initialize song stomp\n");

    set.powerup = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_powerup.wav"));
    if (!set.powerup)
        printf("couldn't initialize song powerup\n");

    set.powerdown = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_pipe.wav"));
    if (!set.powerdown)
        printf("couldn't initialize song powerdown\n");

    set.up = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_1-up.wav"));
    if (!set.up)
        printf("couldn't initialize song up\n");

    set.powerup_appears = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_powerup_appears.wav"));
    if (!set.powerup_appears)
        printf("couldn't initialize song powerup_appears\n");

    set.coin = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_coin.wav"));
    if (!set.coin)
        printf("couldn't initialize song coin\n");

    set.flagpole = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_flagpole.wav"));
    if (!set.flagpole)
        printf("couldn't initialize song flagpole\n");

    set.kick = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_kick.wav"));
    if (!set.kick)
        printf("couldn't initialize song kick\n");

    set.warning = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_warning.wav"));
    if (!set.warning)
        printf("couldn't initialize song warning\n");

    set.stage_clear = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_stage_clear.wav"));
    if (!set.stage_clear)
        printf("couldn't initialize song stage_clear\n");

    set.world_clear = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_world_clear.wav"));
    if (!set.world_clear)
        printf("couldn't initialize song world_clear\n");

    al_attach_sample_instance_to_mixer(set.stomp, set.sound_mixer);
    al_set_sample_instance_playmode(set.stomp, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.breakBlock, set.sound_mixer);
    al_set_sample_instance_playmode(set.breakBlock, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.bump, set.sound_mixer);
    al_set_sample_instance_playmode(set.bump, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.coin, set.sound_mixer);
    al_set_sample_instance_playmode(set.coin, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.powerup_appears, set.sound_mixer);
    al_set_sample_instance_playmode(set.powerup_appears, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.powerup, set.sound_mixer);
    al_set_sample_instance_playmode(set.powerup, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.up, set.sound_mixer);
    al_set_sample_instance_playmode(set.up, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.powerdown, set.sound_mixer);
    al_set_sample_instance_playmode(set.powerdown, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.jump, set.sound_mixer);
    al_set_sample_instance_playmode(set.jump, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.click_pause, set.sound_mixer);
    al_set_sample_instance_playmode(set.click_pause, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.flagpole, set.sound_mixer);
    al_set_sample_instance_playmode(set.flagpole, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.kick, set.sound_mixer);
    al_set_sample_instance_playmode(set.kick, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.warning, set.sound_mixer);
    al_set_sample_instance_playmode(set.warning, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.die, set.music_mixer);
    al_set_sample_instance_playmode(set.die, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.gameOver, set.music_mixer);
    al_set_sample_instance_playmode(set.gameOver, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.stage_clear, set.music_mixer);
    al_set_sample_instance_playmode(set.stage_clear, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.world_clear, set.music_mixer);
    al_set_sample_instance_playmode(set.world_clear, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(set.songInstance, set.music_mixer);
    al_set_sample_instance_playmode(set.songInstance, ALLEGRO_PLAYMODE_LOOP);

    al_attach_sample_instance_to_mixer(set.star, set.music_mixer);
    al_set_sample_instance_playmode(set.star, ALLEGRO_PLAYMODE_LOOP);

    al_attach_sample_instance_to_mixer(set.pause, set.music_mixer);
    al_set_sample_instance_playmode(set.pause, ALLEGRO_PLAYMODE_LOOP);

    al_attach_mixer_to_mixer(set.sound_mixer, set.master_mixer);
    al_attach_mixer_to_mixer(set.music_mixer, set.master_mixer);

    return set;
}

void sonTimer(int timer, sound soundEffect, joueur *personnage, settings *system)
{
    float speed = 1.3;
    timer = tpsNiveau - timer / REFRESH_RATE;

    if (timer <= 100 && timer >= 99)
    {
        al_stop_sample_instance(soundEffect.songInstance);
        al_stop_sample_instance(soundEffect.star);
        al_play_sample_instance(soundEffect.warning);
    }
    else
    {
        switch (system->mode)
        {
        case PLAYING_MAP:
            if (personnage->etoile == 0)
            {
                if (timer <= 99)
                {
                    al_set_sample_instance_speed(soundEffect.songInstance, speed);
                    al_play_sample_instance(soundEffect.songInstance);
                }
                else
                {
                    speed = 1;
                    al_set_sample_instance_speed(soundEffect.songInstance, speed);
                    al_play_sample_instance(soundEffect.songInstance);
                }
            }else{
                al_play_sample_instance(soundEffect.star);
            }
            break;
        }
    }
}

void destructLib(ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, sound soundEffect)
{

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    al_destroy_sample_instance(soundEffect.songInstance);
    al_destroy_sample_instance(soundEffect.star);
    al_destroy_sample_instance(soundEffect.pause);
    al_destroy_sample_instance(soundEffect.stomp);
    al_destroy_sample_instance(soundEffect.click_pause);
    al_destroy_sample_instance(soundEffect.breakBlock);
    al_destroy_sample_instance(soundEffect.bump);
    al_destroy_sample_instance(soundEffect.coin);
    al_destroy_sample_instance(soundEffect.powerup_appears);
    al_destroy_sample_instance(soundEffect.powerup);
    al_destroy_sample_instance(soundEffect.up);
    al_destroy_sample_instance(soundEffect.jump);
    al_destroy_sample_instance(soundEffect.die);
    al_destroy_sample_instance(soundEffect.powerdown);
    al_destroy_sample_instance(soundEffect.gameOver);
    al_destroy_sample_instance(soundEffect.flagpole);
    al_destroy_sample_instance(soundEffect.kick);
    al_destroy_sample_instance(soundEffect.stage_clear);
    al_destroy_sample_instance(soundEffect.world_clear);

    al_destroy_mixer(soundEffect.music_mixer);
    al_destroy_mixer(soundEffect.sound_mixer);
    al_destroy_mixer(soundEffect.master_mixer);
    al_destroy_voice(soundEffect.voice);
}
