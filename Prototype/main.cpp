/// PSTE - Groupe 123

/******************************************

Code insipé du projet piscine de
Guillaume Carrabin, Pierre Balland
et Victor Aymard

****************************************/




#include "grman/grman.h"
#include <iostream>
#include "graph.h"

void menu();
int main()
{

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    menu();

    grman::fermer_allegro();

    //nettoyage du terminal
    system("cls");
    std::cout <<"Au revoir"<<std::endl;

    return 0;
}


void menu()
{
    BITMAP* fond ;
    BITMAP* buffer ;
    fond = load_bitmap("menu.jpg", NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    blit(fond, buffer, 0,0,0,0,1000, 740);
    blit(buffer, screen, 0,0,0,0,1000, 740);




    grman::set_pictures_path("pics");
    bool x = false, secu = false;
    Graph g;
    std::string adresse;
    std::string nom1 = "graphe1-Copie";
    std::string nom4 = "parcellaire_extrait.png"; ///inserer le nom de l'image de fond




    while ( !key[KEY_ESC] )
    {
        ///---------------------------------------------------------------------

        x= false;

        std::string nom = " ";
        secu=false;

        if(mouse_b&1 && 430 < mouse_x &&  mouse_x < 570 && 220< mouse_y && mouse_y < 260 )///graphe1
        {
            key[KEY_R] = false;
            key[KEY_M]=false;
            key[KEY_N]=false;
             std::cout <<"Veuillez enter l'adresse"<<std::endl;
                std::cin>>adresse;

            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom1,nom4);
            }
            while (x == true)
            {
                g.update(nom1);
                grman::mettre_a_jour();

                if(key[KEY_R] )
                {
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();
                }
            }
        }
        else  if(mouse_b&1 && 360 < mouse_x &&  mouse_x < 640 && 320< mouse_y && mouse_y < 360)///catégorie
        {
            key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = true;
                  std::cout <<"categorie"<<std::endl;
            }
        }
        else  if(mouse_b&1 && 340 < mouse_x &&  mouse_x < 660 && 420< mouse_y && mouse_y < 460 )///type
        {
            key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = true;
                std::cout <<"type"<<std::endl;
            }
        }
        else  if(mouse_b&1 && 320 < mouse_x &&  mouse_x < 690 && 520< mouse_y && mouse_y < 560 )///quitter
        {
                std::cout <<"quitter"<<std::endl;
            key[KEY_ESC]=true;
        }
    }
}
END_OF_MAIN();
