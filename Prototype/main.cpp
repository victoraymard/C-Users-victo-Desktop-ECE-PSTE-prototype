/// PSTE - Groupe 123

/******************************************

Code insipé du projet piscine de
Guillaume Carrabin, Pierre Balland
et Victor Aymard

Realisé par Victor Aymard

****************************************/


#include <chrono>
#include<thread>
#include "grman/grman.h"
#include <iostream>
#include "graph.h"

#define COINX 5.5
#define COINY 5.5
#define ERREURPOS 11

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
    BITMAP* popup ;
    popup = load_bitmap("popupbis.png", NULL);//pas dans le dossier pics

     BITMAP* popuptest ;
    popuptest = load_bitmap("popup.jpg", NULL);//pas dans le dossier pics

    std::vector<Vertex> mainVertices;




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
    std::string type = "0";
    std::string nom1 = "graphe1-Copie";
    std::string nom4 = "parcellaire_extrait.png"; ///inserer le nom de l'image de fond

    std::string position = "";



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
                g.recuperation(nom1,nom4, mainVertices);

                for (int i=0; i<mainVertices.size(); i++)
                {
                    std::cout <<"x "<<mainVertices[i].posx<<"       ";
                    std::cout <<"y "<<mainVertices[i].posy<<"       ";
                    std::cout <<"idx "<<mainVertices[i].idx<<std::endl;
                }
                position = "space";

            }
            while (x == true)
            {
                g.update(nom1);
                grman::mettre_a_jour();


                /// poteaux---------------------------------------------------------------------------------------------------------------------------------

                for (int i=0; i<mainVertices.size(); i++)
                {
                   /// rectfill(screen,mainVertices[i].posx-COINX+2.5*ERREURPOS,mainVertices[i].posy-COINY+0.9*ERREURPOS,mainVertices[i].posx+COINX+2.6*ERREURPOS,mainVertices[i].posy+COINY+1*ERREURPOS, makecol(255, 0, 0));/// pour visualiser la position des sommets

                     //si on met mouse_b sans clique
                    if(mouse_b&1 && mainVertices[i].posx-COINX+2.5*ERREURPOS< mouse_x &&  mouse_x < mainVertices[i].posx+COINX+2.6*ERREURPOS && mainVertices[i].posy-COINY+0.9*ERREURPOS< mouse_y && mouse_y < mainVertices[i].posy+COINY+1*ERREURPOS && position == "space")///graphe200 +20x
                    //if(mouse_b&1 && 408< mouse_x &&  mouse_x < 428 && 602< mouse_y && mouse_y < 622 && position == "space")///graphe200 +20x
                    {
                        std::cout <<mainVertices[i].idx<<std::endl;
                        std::cout <<mainVertices[i].numHydrant<<std::endl;
                        std::cout <<mainVertices[i].infosHydrant<<std::endl;

                        /// surbrillance du sommet
//                        m_box_label_idx.set_bg_color(ROUGE);

                        /// cercles



                        ///pop up

                        //blit(fond, buffer, 0,0,0,0,1000, 750);
                        blit(popuptest, buffer, 0,0,0,0,1000, 750); //ajout d'un sommet avec  une image
                        blit(buffer, screen, 0,0,0,0,1000,750);

                       // grman::mettre_a_jour();
                        std::this_thread::sleep_for (std::chrono::seconds(2));//pensant 2 s


                        //std::cout <<"poteau 200\n"; //diametre 250
                        //std::cout <<"diametre 200\n3 LGP\n7 LG\n7 LDV\n\n";
                    }
                }

               /*   if(mouse_b&1 && 408< mouse_x &&  mouse_x < 428 && 602< mouse_y && mouse_y < 622 && position == "space")///graphe200 +20x
                {
                    //x=false;
                    std::cout <<"poteau 200\n"; //diametre 250
                    std::cout <<"diametre 200\n3 LGP\n7 LG\n7 LDV\n\n";
                    //   blit(fond, buffer, 0,0,0,0,1000, 740);
                    //blit(buffer, screen, 0,0,0,0,1000, 740);
                }

                 if(mouse_b&1 && 350< mouse_x &&  mouse_x < 370 && 47< mouse_y && mouse_y < 67 && position == "space" )///graphe201 +20x
                   {
                       //x=false;
                       std::cout <<"poteau 201\n"; //diametre 250
                       std::cout <<"diametre 250\n5 LGP\n11 LG\n11 CDV\n1 vector\n\n";
                       //   blit(fond, buffer, 0,0,0,0,1000, 740);
                       //blit(buffer, screen, 0,0,0,0,1000, 740);
                   }
                   if(mouse_b&1 && 386< mouse_x &&  mouse_x < 404 && 353< mouse_y && mouse_y < 368  && position == "space")///graphe197 +20x
                   {
                       //x=false;
                       std::cout <<"poteau 197\n"; //diametre 250
                       std::cout <<"diametre 300\n8 LGP\n16 LG\n16 LDV\n2 vector\n\n";
                       //   blit(fond, buffer, 0,0,0,0,1000, 740);
                       //blit(buffer, screen, 0,0,0,0,1000, 740);
                   }*/
                ///-----------------------------------------------------------------------------------------------------------------------------------------------
                if(key[KEY_R] )
                {
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();
                }

                /// chanement de parcelle -----------------------------------------------------
                if(key[KEY_SPACE] )
                {
                    position = "space";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation(nom1,"parcellaire_extrait.png", mainVertices);
                }
                if(key[KEY_LEFT] )
                {
                    position = "left";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation(nom1,"parcellaire_left.png", mainVertices);
                }
                if(key[KEY_RIGHT] )
                {
                    position = "right";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation(nom1,"parcellaire_right.png", mainVertices);
                }
                if(key[KEY_UP] )
                {
                    position = "up";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation(nom1,"parcellaire_up.png", mainVertices);
                }
                if(key[KEY_DOWN] )
                {
                    position = "down";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation(nom1,"parcellaire_down.png", mainVertices);
                }
                ///----------------------------------------------------------------------------
            }
        }
        else  if(mouse_b&1 && 360 < mouse_x &&  mouse_x < 640 && 320< mouse_y && mouse_y < 360)///catégorie
        {
            key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = false;
                while(!secu)
                {
                    std::cout <<"veuillez selectionner le type de feu :\n1 - feu de poubelle\n2 - feu de voiture\n3 - feu de maison\n4 - feu d appartement\n5 - feu de hangar"<<std::endl<<std::endl;
                    std::cin >> type;
                    // if(type!='1' ||type!='2' ||type!='3' ||type!='4' ||type!='5' )std::cout <<"type inconnu"<<std::endl;
                    if(type!="1" &&type!="2" &&type!="3" &&type!="4" &&type!="5" )
                        std::cout <<"type inconnu"<<std::endl;
                    else
                        secu = true;
                }
            }
            std::cout << "il ne se passe rien...";
            //coder les actions à faire
        }
        else  if(mouse_b&1 && 340 < mouse_x &&  mouse_x < 660 && 420< mouse_y && mouse_y < 460 )///type
        {
            key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = false;
                while(!secu)
                {
                    std::cout <<"veuillez selectionner le probleme :\n1 - incendie\n2 - personne inconsciente\n3 - probleme domestique\n4 - tentez de gagner une voirure d'une valeur de 50 000 000 euros !\n5 - la reponse D"<<std::endl<<std::endl;
                    std::cin >> type;
                    // if(type!='1' ||type!='2' ||type!='3' ||type!='4' ||type!='5' )std::cout <<"type inconnu"<<std::endl;
                    if(type!="1" &&type!="2" &&type!="3" &&type!="4" &&type!="5" )
                        std::cout <<"categorie inconnue"<<std::endl;
                    else
                        secu = true;
                }
                std::cout << "il ne se passe rien...";
                //coder les actions à faire


            }
        }
        else  if(mouse_b&1 && 320 < mouse_x &&  mouse_x < 690 && 520< mouse_y && mouse_y < 560 )///quitter
        {
            std::cout <<"quitter"<<std::endl;
            key[KEY_ESC]=true;
        }
    }
    g.credits();//affiche les crédis
    g.update(nom1);
    grman::mettre_a_jour();
    std::this_thread::sleep_for (std::chrono::seconds(2));//pensant 2 s
}
END_OF_MAIN();
