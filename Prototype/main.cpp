/// PSTE - Groupe 234

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

std::string ecritureTerminal( std::string s);
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
    BITMAP* poster ;
    poster = load_bitmap("posterrr.png", NULL);//pas dans le dossier pics

    BITMAP* map1 ;
    map1 = load_bitmap("map1.png", NULL);//pas dans le dossier pics

    BITMAP* popup ;
    popup = load_bitmap("popupbis.png", NULL);//pas dans le dossier pics

    BITMAP* fondviolet;
    fondviolet = load_bitmap("fondviolet.png", NULL);

    BITMAP* popuptest ;
    popuptest = load_bitmap("popup.jpg", NULL);//pas dans le dossier pics

    std::vector<Vertex> mainVertices;
    std::vector<Edge> mainEdges;
    std::vector<VertexInterface> mainInterfacedVertices;

    bool premierpassage = true;


    BITMAP* fond ;
    BITMAP* buffer ;
    fond = load_bitmap("posterr.png", NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    blit(fond, buffer, 0,0,0,0,1000, 740);
    blit(buffer, screen, 0,0,0,0,1000, 740);




    grman::set_pictures_path("pics");
    bool x = false, secu = false;
    Graph g;
    std::string adresse;
    std::string type = "0";
    std::string nom1 = "graphe2";
    std::string nom4 = "parcellaire_extrait.png"; ///inserer le nom de l'image de fond

    std::string zone1 = "sarcelles_flanades";
    std::string zone2 = "sarcelles_ouest";
    std::string zone3 = "sarcelles_est";
    std::string zone4 = "sarcelles_nord";
    std::string zone5 = "sarcelles_sud";

    std::string position = "";
    char c = '_';
    std::string s = "";

    int incidentX =0;
    int incidentY =0;



    while ( !key[KEY_ESC] )
    {
        ///---------------------------------------------------------------------

        x= false;

        std::string nom = " ";
        secu=false;

        if(mouse_b&1 && 427 < mouse_x &&  mouse_x < 581 && 213< mouse_y && mouse_y < 241 )/// hydrants
        {
            key[KEY_R] = false;
            key[KEY_M]=false;
            key[KEY_N]=false;

            x = true;
            if( secu == false)
            {
                secu = false;
                while(!secu)
                {
                    std::cout <<"Veuillez enter l'adresse"<<std::endl;
                    std::cin>>adresse;

                    if(adresse!=zone1 &&adresse!=zone2 &&adresse!=zone3 &&adresse!=zone4 &&adresse!=zone5 )
                        std::cout <<"la zone n est pas encore couverte par le programme, veuillez reiterer l opperation"<<std::endl;
                    else
                        secu = true;
                }
                if (adresse==zone1)
                    g.recuperation(nom1,nom4, mainVertices, mainEdges);
                else if(adresse==zone2)
                    g.recuperation("vide","parcellaire_left.png", mainVertices, mainEdges);
                else if(adresse==zone3)
                    g.recuperation("vide","parcellaire_right.png", mainVertices, mainEdges);
                else if(adresse==zone4)
                    g.recuperation("vide","parcellaire_up.png", mainVertices, mainEdges);
                else if(adresse==zone5)
                    g.recuperation("vide","parcellaire_down.png", mainVertices, mainEdges);
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
                        s= mainVertices[i].infosHydrant;
                        std::cout <<mainVertices[i].idx<<std::endl;
                        std::cout <<mainVertices[i].numHydrant<<std::endl;
                        std::cout<< ecritureTerminal(s) <<std::endl;

                        /// cercle


                        circlefill( screen, mainVertices[i].posx+2.5*ERREURPOS,mainVertices[i].posy+0.9*ERREURPOS, 80, VERTCLAIR);
                        circlefill( screen, mainVertices[i].posx+2.5*ERREURPOS,mainVertices[i].posy+0.9*ERREURPOS, 50, ROUGE);
                        circlefill( screen, mainVertices[i].posx+2.5*ERREURPOS,mainVertices[i].posy+0.9*ERREURPOS, 25, VERT);

                        //  std::this_thread::sleep_for (std::chrono::seconds(2));//pensant 2 s
                        /// surbrillance du sommet
//                        m_box_label_idx.set_bg_color(ROUGE);



                        /*   VertexInterface *vii= new VertexInterface(mainVertices[i].idx, mainVertices[i].posx, mainVertices[i].posy);
                           vii->m_top_box.set_pos(50, 50);
                           vii->m_top_box.set_dim(50,50);
                           vii->m_top_box.set_bg_color(ROSE);


                        VertexInterface *vi = new VertexInterface(mainVertices[i].idx, mainVertices[i].posx, mainVertices[i].posy);
                        // Ajout de la top box de l'interface de sommet


                        vi->m_box_label_idx.set_color(BLEUCLAIR);
                        vi->m_box_label_idx.set_bg_color(BLEUCLAIR);
                        vi->m_top_box.set_bg_color(BLEUCLAIR);
                        //vi->m_top_box.set_m();
                        vi->m_box_label_idx.set_message("coucou");*/

                        /// arettes
                        for (int j =0; j<mainEdges.size(); j++)
                        {
                            if (mainEdges[j].reseau=mainVertices[i].reseau)
                                g.affichage_arette(mainEdges[j].idx, mainEdges[j].id_vert1, mainEdges[j].id_vert2);
                        }

                        std::this_thread::sleep_for (std::chrono::seconds(2));//pensant 2 s

                        for (int j =0; j<mainEdges.size(); j++)
                        {
                            if (mainEdges[j].reseau=mainVertices[i].reseau)
                                g.test_remove_edge(j);
                        }



                        ///pop up
                        /*
                                                blit(fondviolet, buffer, 0,0,0,0,1000, 750);
                                                blit(buffer, screen, 0,0,0,0,1000,750);
                                                blit(popuptest, buffer, 0,0,0,0,1000, 750); //ajout d'un sommet avec  une image
                                                blit(buffer, screen, 0,0,0,0,1000,750);

                        */


                        // grman::mettre_a_jour();


                        //key[KEY_SPACE]=true;
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
                    g.recuperation(nom1,"parcellaire_extrait.png", mainVertices, mainEdges);
                }
                if(key[KEY_LEFT] )
                {
                    position = "left";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_left.png", mainVertices, mainEdges);
                }
                if(key[KEY_RIGHT] )
                {
                    position = "right";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_right.png", mainVertices, mainEdges);
                }
                if(key[KEY_UP] )
                {
                    position = "up";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_up.png", mainVertices, mainEdges);
                }
                if(key[KEY_DOWN] )
                {
                    position = "down";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_down.png", mainVertices, mainEdges);
                }
                ///----------------------------------------------------------------------------
            }
        }
        else  if(mouse_b&1 && 389 < mouse_x &&  mouse_x < 619 && 301< mouse_y && mouse_y < 336)/// plans
        {

            key[KEY_R] = false;
            key[KEY_M]=false;
            key[KEY_N]=false;



            x = true;

            if( secu == false)
            {

                secu = false;
                while(!secu)
                {
                    std::cout <<"Veuillez enter l'adresse"<<std::endl;
                    std::cin>>adresse;

                    if(adresse!=zone1 &&adresse!=zone2 &&adresse!=zone3 &&adresse!=zone4 &&adresse!=zone5 )
                        std::cout <<"la zone n est pas encore couverte par le programme, veuillez reiterer l opperation"<<std::endl;
                    else
                        secu = true;
                }
                if (adresse==zone1)
                    g.recuperation("vide","map1.png", mainVertices, mainEdges);
                else if(adresse==zone2)
                    g.recuperation("vide","map1l.png", mainVertices, mainEdges);
                else if(adresse==zone3)
                    g.recuperation("vide","map1r.png", mainVertices, mainEdges);
                else if(adresse==zone4)
                    g.recuperation("vide","map1u.png", mainVertices, mainEdges);
                else if(adresse==zone5)
                    g.recuperation("vide","map1d.png", mainVertices, mainEdges);

            }
            while (x == true)
            {
                g.update(nom1);
                grman::mettre_a_jour();

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
                    std::cout <<"Sarcelles flanades"<<std::endl;
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","map1.png", mainVertices, mainEdges);
                }
                if(key[KEY_LEFT] )
                {
                    std::cout <<"Sarcelles Ouest"<<std::endl;
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","map1l.png", mainVertices, mainEdges);
                }
                if(key[KEY_RIGHT] )
                {
                    std::cout <<"Sarcelles Est"<<std::endl;
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","map1r.png", mainVertices, mainEdges);
                }
                if(key[KEY_UP] )
                {
                    std::cout <<"Sarcelles Nord"<<std::endl;
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","map1u.png", mainVertices, mainEdges);
                }
                if(key[KEY_DOWN] )
                {
                    std::cout <<"Sarcelles Sud"<<std::endl;
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","map1d.png", mainVertices, mainEdges);
                }
                ///----------------------------------------------------------------------------
            }


            //std::cout << "il ne se passe rien...";
            //coder les actions à faire
        }
        else  if(mouse_b&1 && 399 < mouse_x &&  mouse_x < 605 && 400< mouse_y && mouse_y < 431 )/// suggestions
        {
            key[KEY_R] = false;
            key[KEY_M]=false;
            key[KEY_N]=false;
            premierpassage = true;

            x = true;
            if( secu == false)
            {
                secu = false;
                while(!secu)
                {
                    std::cout <<"Veuillez enter l'adresse"<<std::endl;
                    std::cin>>adresse;
                    if(adresse!=zone1 &&adresse!=zone2 &&adresse!=zone3 &&adresse!=zone4 &&adresse!=zone5 )
                        std::cout <<"la zone n est pas encore couverte par le programme, veuillez reiterer l opperation"<<std::endl;
                    else
                        secu = true;
                }
                if (adresse==zone1)
                    g.recuperation(nom1,nom4, mainVertices, mainEdges);
                else if(adresse==zone2)
                    g.recuperation("vide","parcellaire_left.png", mainVertices, mainEdges);
                else if(adresse==zone3)
                    g.recuperation("vide","parcellaire_right.png", mainVertices, mainEdges);
                else if(adresse==zone4)
                    g.recuperation("vide","parcellaire_up.png", mainVertices, mainEdges);
                else if(adresse==zone5)
                    g.recuperation("vide","parcellaire_down.png", mainVertices, mainEdges);
                position = "space";


                secu = false;
                while(!secu)
                {
                    std::cout <<"Veuillez indiquer le lieu de l incident"<<std::endl;
                    std::cin>>type;

                    if(type!="tour_a" &&type!="tour_b" &&type!="tour_c" &&type!="tour_d" &&type!="magasin" )
                        std::cout <<"Ce lieu n est pas encore couvert par le programme, veuillez reiterer l opperation."<<std::endl;
                    else
                        secu = true;
                }
                if (type == "tour_a")
                {
                    std::cout<< "Suggestion 1:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 191"<<std::endl;
                    std::cout<< "Alimentation sur 4 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 2 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne peut supporter qu un seul vehicule en plus"<<std::endl<<std::endl;

                    std::cout<< "Suggestion 2:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 223"<<std::endl;
                    std::cout<< "Alimentation sur 3 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 1 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne supporte plus d autre vehicules"<<std::endl<<std::endl;

                    std::cout<< "Demande de renfort CEDA"<<std::endl;
                    std::cout<< "Alimentation sur le poteau 128"<<std::endl;
                    std::cout<< "Utiliser 1 Vector, 3 GL et 3 LDV"<<std::endl;
                    std::cout<< "Le reseau peut supporter l'ensemble des moyens necessaires"<<std::endl<<std::endl;
                    incidentX = 400;
                    incidentY = 540;

                }
                else if (type == "magasin")
                {
                    std::cout<< "Suggestion 1:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 200"<<std::endl;
                    std::cout<< "Alimentation sur 4 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 2 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne peut supporter qu un seul vehicule en plus"<<std::endl<<std::endl;

                    std::cout<< "Suggestion 2:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 199"<<std::endl;
                    std::cout<< "Alimentation sur 3 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 1 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne supporte plus d autre vehicules"<<std::endl<<std::endl;

                    std::cout<< "Demande de renfort CEDA"<<std::endl;
                    std::cout<< "Alimentation sur le poteau 128"<<std::endl;
                    std::cout<< "Utiliser 1 Vector, 3 GL et 3 LDV"<<std::endl;
                    std::cout<< "Le reseau peut supporter l'ensemble des moyens necessaires"<<std::endl<<std::endl;
                    incidentX = 400;
                    incidentY = 540;
                }
                else if (type == "tour_b")
                {
                    std::cout<< "Suggestion 1:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 198"<<std::endl;
                    std::cout<< "Alimentation sur 4 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 2 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne peut supporter qu un seul vehicule en plus"<<std::endl<<std::endl;

                    std::cout<< "Suggestion 2:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 222"<<std::endl;
                    std::cout<< "Alimentation sur 3 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 1 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne supporte plus d autre vehicules"<<std::endl<<std::endl;

                    std::cout<< "Demande de renfort CEDA"<<std::endl;
                    std::cout<< "Alimentation sur le poteau 128"<<std::endl;
                    std::cout<< "Utiliser 1 Vector, 3 GL et 3 LDV"<<std::endl;
                    std::cout<< "Le reseau peut supporter l'ensemble des moyens necessaires"<<std::endl<<std::endl;
                    incidentX = 400;
                    incidentY = 540;
                }
                else if (type == "tour_c")
                {
                    std::cout<< "Suggestion 1:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 197"<<std::endl;
                    std::cout<< "Alimentation sur 4 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 2 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne peut supporter qu un seul vehicule en plus"<<std::endl<<std::endl;

                    std::cout<< "Suggestion 2:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 221"<<std::endl;
                    std::cout<< "Alimentation sur 3 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 1 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne supporte plus d autre vehicules"<<std::endl<<std::endl;

                    std::cout<< "Demande de renfort CEDA"<<std::endl;
                    std::cout<< "Alimentation sur le poteau 128"<<std::endl;
                    std::cout<< "Utiliser 1 Vector, 3 GL et 3 LDV"<<std::endl;
                    std::cout<< "Le reseau peut supporter l'ensemble des moyens necessaires"<<std::endl<<std::endl;
                    incidentX = 400;
                    incidentY = 540;
                }
                else if (type == "tour_d")
                {
                    std::cout<< "Suggestion 1:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 196"<<std::endl;
                    std::cout<< "Alimentation sur 4 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 2 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne peut supporter qu un seul vehicule en plus"<<std::endl<<std::endl;

                    std::cout<< "Suggestion 2:"<<std::endl;
                    std::cout<< "Utilisation du poteau numero 212"<<std::endl;
                    std::cout<< "Alimentation sur 3 lignes"<<std::endl;
                    std::cout<< "Utiliser 2 GL et 1 LDV"<<std::endl;
                    std::cout<< "Attention, le reseau ne supporte plus d autre vehicules"<<std::endl<<std::endl;

                    std::cout<< "Demande de renfort CEDA"<<std::endl;
                    std::cout<< "Alimentation sur le poteau 128"<<std::endl;
                    std::cout<< "Utiliser 1 Vector, 3 GL et 3 LDV"<<std::endl;
                    std::cout<< "Le reseau peut supporter l'ensemble des moyens necessaires"<<std::endl<<std::endl;
                    incidentX = 400;
                    incidentY = 540;
                }
            }
            while (x == true)
            {
                g.update(nom1);
                grman::mettre_a_jour();

                ///position de l'incident
              if (premierpassage)
               {
                    circlefill( screen, incidentX,incidentY, 14, JAUNE); // sur la position de la tour
                    circlefill( screen, incidentX,incidentY, 12, ROUGE); // sur la position de la tour

                   system("PAUSE");
                   premierpassage=false;
               }
                /// poteaux---------------------------------------------------------------------------------------------------------------------------------

                for (int i=0; i<mainVertices.size(); i++)
                {
                    /// rectfill(screen,mainVertices[i].posx-COINX+2.5*ERREURPOS,mainVertices[i].posy-COINY+0.9*ERREURPOS,mainVertices[i].posx+COINX+2.6*ERREURPOS,mainVertices[i].posy+COINY+1*ERREURPOS, makecol(255, 0, 0));/// pour visualiser la position des sommets

                    //si on met mouse_b sans clique
                    if(mouse_b&1 && mainVertices[i].posx-COINX+2.5*ERREURPOS< mouse_x &&  mouse_x < mainVertices[i].posx+COINX+2.6*ERREURPOS && mainVertices[i].posy-COINY+0.9*ERREURPOS< mouse_y && mouse_y < mainVertices[i].posy+COINY+1*ERREURPOS && position == "space")///graphe200 +20x
                        //if(mouse_b&1 && 408< mouse_x &&  mouse_x < 428 && 602< mouse_y && mouse_y < 622 && position == "space")///graphe200 +20x
                    {
                        s= mainVertices[i].infosHydrant;
                        std::cout <<std::endl;
                        std::cout <<mainVertices[i].numHydrant<<std::endl;
                        std::cout<< ecritureTerminal(s) <<std::endl;

                        /// surbrillance du sommet
//                        m_box_label_idx.set_bg_color(ROUGE);

                        /// arettes  --> le mieux est de le faire amnuellement / penser à les supprimer après

                        /// reseau 1
                        if (mainVertices[i].reseau==1)
                        {
                            g.affichage_arette(9, 9, 9);
                            g.affichage_arette(11, 11, 11);
                            g.affichage_arette(17, 17, 17);
                            g.affichage_arette(18, 18, 18);
                        }

                        /// reseau 2
                        else if (mainVertices[i].reseau==2)
                        {
                            g.affichage_arette(19,19 ,19 );
                            g.affichage_arette(20,20,20 );
                            g.affichage_arette(22, 22, 22);
                            g.affichage_arette(25, 25, 25);
                        }
                       /// reseau 3
                        else if (mainVertices[i].reseau==3)
                        {
                            g.affichage_arette(24,24 ,24 );
                        }
                        /// reseau 4
                        else if (mainVertices[i].reseau==4)
                        {
                            g.affichage_arette(15, 15, 15);
                        }
                        /// reseau 5
                        else if (mainVertices[i].reseau==5)
                        {
                            g.affichage_arette(7, 7, 7);
                            g.affichage_arette(8, 8, 8);
                            g.affichage_arette(10, 10, 10);
                        }
                        /// reseau 7
                        else if (mainVertices[i].reseau==7)
                        {
                            g.affichage_arette(28, 28, 28);
                        }
                        /// reseau 13
                        else if (mainVertices[i].reseau==13)
                        {
                            g.affichage_arette(4, 4, 4);
                        }
                        /// reseau 14
                        else if (mainVertices[i].reseau==14)
                        {
                            g.affichage_arette(6, 6, 6);
                        }
                        /// reseau 15
                        else if (mainVertices[i].reseau==15)
                        {
                            g.affichage_arette(1, 1, 1);
                            g.affichage_arette(12, 12, 12);
                        }
                        /// reseau 16
                        else if (mainVertices[i].reseau==16)
                        {
                            g.affichage_arette(2, 2, 2);
                            g.affichage_arette(13, 13, 13);
                        }
                        /// cercle


                        circlefill( screen, mainVertices[i].posx+2.5*ERREURPOS,mainVertices[i].posy+0.9*ERREURPOS, 80, BLEU);
                        circlefill( screen, mainVertices[i].posx+2.5*ERREURPOS,mainVertices[i].posy+0.9*ERREURPOS, 50, ROUGE);
                        circlefill( screen, mainVertices[i].posx+2.5*ERREURPOS,mainVertices[i].posy+0.9*ERREURPOS, 25, NOIR);

                          std::this_thread::sleep_for (std::chrono::seconds(1));//pensant 1 s
                    }
                }
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
                    g.recuperation(nom1,"parcellaire_extrait.png", mainVertices, mainEdges);
                }
                if(key[KEY_LEFT] )
                {
                    position = "left";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_left.png", mainVertices, mainEdges);
                }
                if(key[KEY_RIGHT] )
                {
                    position = "right";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_right.png", mainVertices, mainEdges);
                }
                if(key[KEY_UP] )
                {
                    position = "up";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_up.png", mainVertices, mainEdges);
                }
                if(key[KEY_DOWN] )
                {
                    position = "down";
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();

                    x = true;
                    g.recuperation("vide","parcellaire_down.png", mainVertices, mainEdges);
                }
                ///----------------------------------------------------------------------------
            }
        }
        else  if(mouse_b&1 && 319 < mouse_x &&  mouse_x < 687 && 490< mouse_y && mouse_y < 526 )///quitter
        {
            std::cout <<"quitter"<<std::endl;
            key[KEY_ESC]=true;
        }
        else  if(mouse_b&1 && 835 < mouse_x &&  mouse_x < 978 && 568< mouse_y && mouse_y < 611 )///infos complémentaires
        {
            key[KEY_R] = false;

 x = true;
            if( secu == false)
            {
                secu = false;
                while( key[KEY_R] ==false )
                {

            std::cout <<"informations complémentaires"<<std::endl;
            blit(poster, buffer, 0,0,0,0,1000, 740);
            blit(buffer, screen, 0,0,0,0,1000, 740);
                secu=true;

                }
                if( key[KEY_R] =true)
                {
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                blit(buffer, screen, 0,0,0,0,1000, 740);
                }

            }

        }
    }
    g.credits();//affiche les crédis
    g.update(nom1);
    grman::mettre_a_jour();
    std::this_thread::sleep_for (std::chrono::seconds(2));//pensant 2 s
}
END_OF_MAIN();



std::string ecritureTerminal( std::string s)
{
    std::string ret;
    for(int i = 0 ; i < s.size() ; i++)
    {
        if (s[i] != '_' && s[i] !='x')
            ret += s[i];
        else
            ret+= ' ';
    }
    return ret;
}












/// tâches à faire

// changer les couleurs des arêtes
// areter d'afficher les aretes
//enlever les cout superflus
