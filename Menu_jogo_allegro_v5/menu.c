// ---Bibliotecas---
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//---Definir tamanho da janela do jogo---
#define LARGURA_JANELA 1080
#define ALTURA_JANELA 720
#define largura_imagem 416
#define altura_imagem 96
#define altura_jogo 200
#define altura_historia 300
#define altura_sair 400

//---inicializações---
ALLEGRO_DISPLAY *janela =NULL; 			 //INICIA A JANELA D jA FUNÇÃO ALLEGRO
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;//INICIA O TRATAMENTO DE EVENTOS
ALLEGRO_BITMAP *capa = NULL;        	 // Variável que representa a imagem da capa
ALLEGRO_BITMAP *jogo=NULL;          	 // Variável que representa a imagem com o nome jogo
ALLEGRO_BITMAP *historia=NULL; 			 // Variável que representa a imagem com o nome historia
ALLEGRO_BITMAP *sair=NULL; 	        	 // Variável que representa a imagem com o nome sair
ALLEGRO_BITMAP *inicial=NULL;            // Variável que representa a imagem com o nome sair
ALLEGRO_SAMPLE *musica = NULL;     // Variável que representa a musica tema do menu
ALLEGRO_SAMPLE *sample = NULL;           // Variável que representa a musica de clic no menu

ALLEGRO_SAMPLE_INSTANCE *in_ost=NULL;

//---inicialização de variaveis globais---
int menu=10;             //variavel de controle do menu
int i; 					//variavel para controle de laços

//---prototicos das funções---
void capaMenu(); 		//imprime a capa do menu
void Setup(); 	        //inicia a analise de eventos
void destroy();  		//finalisa o progama

//---função primcipal---
int main()
{
    
    Setup();//inicia a analise de eventos

    capaMenu();//imprime a capa do menu

    //al_attach_audio_stream_to_mixer(musica, al_get_default_mixer()); //lick entre a musica tema do menu do jogo e o mixer
    //al_set_audio_stream_playing(musica, true); //ininico de toca musica tema;

    while(menu) // verifica se o menu ainda esta ativo
    {
        al_play_sample_instance(in_ost);

        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);
       
        if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) menu = 0;
        }
        if(evento.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if ((evento.mouse.x >= LARGURA_JANELA / 2 - al_get_bitmap_width(jogo) / 2) &&
                (evento.mouse.x <= LARGURA_JANELA / 2 + al_get_bitmap_width(jogo) / 2) &&
                (evento.mouse.y >= altura_jogo                                       ) &&
                (evento.mouse.y <= altura_jogo + altura_imagem))
            {
                if(menu!=1)
                {
                    al_play_sample(sample, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //reproduis som de clik
                    menu=1;
                }
                jogo = al_load_bitmap("imagens//jogo2.png");// Carrega a imagem do nome jogo
                al_draw_bitmap(jogo,(LARGURA_JANELA-largura_imagem)/2, altura_jogo, 0);// Desenha a imagem do nome jogo na tela
            }
            else 
            {
                jogo = al_load_bitmap("imagens//jogo1.png");// Carrega a imagem do nome jogo
                al_draw_bitmap(jogo,(LARGURA_JANELA-largura_imagem)/2, altura_jogo, 0);// Desenha a imagem do nome jogo na tela
            }
            if((evento.mouse.x >= LARGURA_JANELA / 2 - al_get_bitmap_width(historia) / 2) &&
               (evento.mouse.x <= LARGURA_JANELA / 2 + al_get_bitmap_width(historia) / 2) &&
               (evento.mouse.y >= altura_historia                                       ) &&
               (evento.mouse.y <= altura_historia + altura_imagem))
            {
                if(menu!=2)
                {
                    al_play_sample(sample, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //reproduis som de clik
                    menu=2;
                }
                historia = al_load_bitmap("imagens//historia2.png");// Carrega a imagem do nome historia
                al_draw_bitmap(historia, (LARGURA_JANELA-largura_imagem)/2,  altura_historia, 0);// Desenha a imagem do nome historia na tela
            }
            else
            {
                historia = al_load_bitmap("imagens//historia1.png");// Carrega a imagem do nome historia
                al_draw_bitmap(historia, (LARGURA_JANELA-largura_imagem)/2,  altura_historia, 0);// Desenha a imagem do nome historia na tela
            }
            if((evento.mouse.x >= LARGURA_JANELA / 2 - al_get_bitmap_width(sair) / 2) &&
               (evento.mouse.x <= LARGURA_JANELA / 2 + al_get_bitmap_width(sair) / 2) &&
               (evento.mouse.y >= altura_sair                                      ) &&
               (evento.mouse.y <= altura_sair + altura_imagem))
            {
                if(menu!=3)
                {
                    al_play_sample(sample, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //reproduis som de clik
                    menu=3;
                }
                sair = al_load_bitmap("imagens//sair2.png");// Carrega a imagem do nome sair
                al_draw_bitmap(sair, (LARGURA_JANELA-largura_imagem)/2,  altura_sair, 0);// Desenha a imagem do nome sair na tela 
            }
            else
            {
                sair = al_load_bitmap("imagens//sair1.png");// Carrega a imagem do nome sair
                al_draw_bitmap(sair, (LARGURA_JANELA-largura_imagem)/2,  altura_sair, 0);// Desenha a imagem do nome sair na tela
            }
            al_flip_display(); // Atualiza a tela
        }
        if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
           if ((evento.mouse.x >= LARGURA_JANELA / 2 - al_get_bitmap_width(jogo) / 2) &&
                (evento.mouse.x <= LARGURA_JANELA / 2 + al_get_bitmap_width(jogo) / 2) &&
                (evento.mouse.y >= altura_jogo                                       ) &&
                (evento.mouse.y <= altura_jogo + altura_imagem))
            {
                al_stop_sample_instance(in_ost);//ao clicar em sair do jogo, a musica tema é finalizada
                al_play_sample(sample, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //reproduis som de clik
                for(i=0;i<2;i++)
                {
                    jogo = al_load_bitmap("imagens//jogo3.png");// Carrega a imagem do nome jogo
                    al_draw_bitmap(jogo,(LARGURA_JANELA-largura_imagem)/2, altura_jogo, 0);// Desenha a imagem do nome jogo na tela
                    al_flip_display(); // Atualiza a tela
                    al_rest(0.5); // delsay 500 ms
                    jogo = al_load_bitmap("imagens//jogo2.png");// Carrega a imagem do nome jogo
                    al_draw_bitmap(jogo,(LARGURA_JANELA-largura_imagem)/2, altura_jogo, 0);// Desenha a imagem do nome jogo na tela
                    al_flip_display(); // Atualiza a tela
                    al_rest(0.5); // delsay 500 ms
                }
            }
            else 
            {
                jogo = al_load_bitmap("imagens//jogo1.png");// Carrega a imagem do nome jogo
                al_draw_bitmap(jogo,(LARGURA_JANELA-largura_imagem)/2, altura_jogo, 0);// Desenha a imagem do nome jogo na tela
            }
            if((evento.mouse.x >= LARGURA_JANELA / 2 - al_get_bitmap_width(historia) / 2) &&
               (evento.mouse.x <= LARGURA_JANELA / 2 + al_get_bitmap_width(historia) / 2) &&
               (evento.mouse.y >= altura_historia                                       ) &&
               (evento.mouse.y <= altura_historia + altura_imagem))
            {
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //reproduis som de clik
                for(i=0;i<2;i++)
                {
                    historia = al_load_bitmap("imagens//historia3.png");// Carrega a imagem do nome historia
                    al_draw_bitmap(historia, (LARGURA_JANELA-largura_imagem)/2,  altura_historia, 0);// Desenha a imagem do nome historia na tela
                    al_flip_display(); // Atualiza a tela
                    al_rest(0.5);      // delsay 500 ms
                    historia = al_load_bitmap("imagens//historia2.png");// Carrega a imagem do nome historia
                    al_draw_bitmap(historia, (LARGURA_JANELA-largura_imagem)/2,  altura_historia, 0);// Desenha a imagem do nome historia na tela
                    al_flip_display(); // Atualiza a tela
                    al_rest(0.5);      // delsay 500 ms  
                }

            }
            else
            {
                historia = al_load_bitmap("imagens//historia1.png");// Carrega a imagem do nome historia
                al_draw_bitmap(historia, (LARGURA_JANELA-largura_imagem)/2,  altura_historia, 0);// Desenha a imagem do nome historia na tela
            }
            if((evento.mouse.x >= LARGURA_JANELA / 2 - al_get_bitmap_width(sair) / 2) &&
               (evento.mouse.x <= LARGURA_JANELA / 2 + al_get_bitmap_width(sair) / 2) &&
               (evento.mouse.y >= altura_sair                                      ) &&
               (evento.mouse.y <= altura_sair + altura_imagem))
            {
                
                al_stop_sample_instance(in_ost);//ao clicar em sair do jogo, a musica tema é finalizada
                al_play_sample(sample, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //reproduis som de clik
                for(i=0;i<2;i++)
                {
                    
                    sair = al_load_bitmap("imagens//sair3.png");// Carrega a imagem do nome sair
                    al_draw_bitmap(sair, (LARGURA_JANELA-largura_imagem)/2,  altura_sair, 0);// Desenha a imagem do nome sair na tela
                    al_flip_display(); // Atualiza a tela
                    al_rest(0.5);      // delsay 500 ms
                    sair = al_load_bitmap("imagens//sair2.png");// Carrega a imagem do nome sair
                    al_draw_bitmap(sair, (LARGURA_JANELA-largura_imagem)/2,  altura_sair, 0);// Desenha a imagem do nome sair na tela
                    al_flip_display(); // Atualiza a tela
                    al_rest(0.5);      // delsay 500 ms a
                    
                }
                menu=0;
                
            }
            else
            {
                sair = al_load_bitmap("imagens//sair1.png");// Carrega a imagem do nome sair
                al_draw_bitmap(sair, (LARGURA_JANELA-largura_imagem)/2,  altura_sair, 0);// Desenha a imagem do nome sair na tela
            } 
        }
    }
 	
    destroy(); //finalisa o progama

	return 0;
}
//--- fim da função main---

//---função capaMenu---
void capaMenu()//imprime a capa do menu
{
    jogo = al_load_bitmap("imagens//jogo1.png");// Carrega a imagem do nome jogo
    al_draw_bitmap(jogo,(LARGURA_JANELA-largura_imagem)/2,  altura_jogo, 0);// Desenha a imagem do nome jogo na tela
    historia = al_load_bitmap("imagens//historia1.png");// Carrega a imagem do nome historia
    al_draw_bitmap(historia, (LARGURA_JANELA-largura_imagem)/2,  altura_historia, 0);// Desenha a imagem do nome historia na tela
    sair = al_load_bitmap("imagens//sair1.png");// Carrega a imagem do nome sair
    al_draw_bitmap(sair, (LARGURA_JANELA-largura_imagem)/2,  altura_sair, 0);// Desenha a imagem do nome sair na tela
    al_flip_display(); // Atualiza a tela
}
//--- fim da função capaMenu---

//---Setup---
void Setup() 					 //inicialisações de eventos
{
    al_init();// Inicializa a Allegro
    //diretivas de entrada
    al_install_mouse(); //inicializa mouse
    al_install_keyboard(); //inicializa teclado
    fila_eventos = al_create_event_queue(); //inicializa fila de eventos
    al_register_event_source(fila_eventos, al_get_mouse_event_source()); //Coloca eventos do mouse na fila de eventos para que sejam analisados
    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); //Coloca eventos do teclado na fila de eventos para que sejam analisados
    //diretivas de audio
    al_install_audio();    // Inicializa o add-on para utilização de audios
    al_init_acodec_addon();// Inicializa o add-on para carregamento de acodes
    al_reserve_samples(1); //Quantidade de canail colocados no mix principal
    sample = al_load_sample("musicas//INTRO_PASSAGEM.wav"); //carrega som de clik na memoria
    musica = al_load_sample("musicas//Intro.wav"); //carreca musica tema do menu do jogo
    //diretivas de imagem
    in_ost= al_create_sample_instance(musica);

    
    /*--------------------------musica tema----------------*/
    al_attach_sample_instance_to_mixer(in_ost,al_get_default_mixer());
    al_set_sample_instance_playmode(in_ost,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(in_ost, 1.0);
    /*---------------------------------------------------------*/

    al_init_image_addon();// Inicializa o add-on para utilização de imagens
    janela = al_create_display(LARGURA_JANELA,ALTURA_JANELA); // Configura a janela
    capa = al_load_bitmap("imagens//capa.png"); // Carrega a imagem de capa
    al_draw_bitmap(capa, 0, 0, 0);// Desenha a imagem de capa na tela
    al_flip_display(); // Atualiza a tela
}
//--- fim da função Setup---

//---função destroy---
void destroy() //finalisa o progama
{
    al_destroy_sample(musica); //finaliza musica tema do menu
    al_destroy_sample(sample);       //finaliza som de clik
	al_destroy_display(janela); // Finaliza a janela
	al_destroy_event_queue(fila_eventos); // Encerra os eventos
    al_destroy_sample_instance(in_ost);
}
//--- fim da função destroy---