#include "graph.h"
#include <sstream>
#include <fstream>
#include<stack>
#include<queue>
#include <set>
#include<algorithm>


namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y)
{
    m_idx = idx;
    //m_thing = thing_name;


    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(11,11);
    //m_top_box.set_moveable();
    m_top_box.set_contained();



    /* // Le slider de réglage de valeur
     m_top_box.add_child( m_slider_value );
     m_slider_value.set_range(mini, maxi);  // Valeurs arbitraires, à adapter...
     m_slider_value.set_dim(20,80);
     m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);*/

    /*// Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);*/

    /* // Une illustration...
     if (pic_name!="")
     {
         m_top_box.add_child( m_img );
         m_img.set_pic_name(pic_name);
         m_img.set_pic_idx(pic_idx);
         m_img.set_gravity_x(grman::GravityX::Right);
     }*/

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_dim(12,12);
    m_box_label_idx.set_no_gravity();
    //m_box_label_idx.set_posy(70);
    m_box_label_idx.set_bg_color(BLEUCLAIR);


    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( patch::to_string(idx) );

    /* m_top_box.add_child(m_bouton1);
     m_bouton1.set_dim(50,12);
     m_bouton1.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
     m_bouton1.set_bg_color(ROUGECLAIR);*/

    /* m_bouton1.add_child( m_msg );
     m_msg.set_message("delete");*/

    /* //nom animal
     m_top_box.add_child(m_nom_animal);
     m_nom_animal.set_frame(90,6, 0, 0 );

     m_nom_animal.add_child(m_nom_animal_label);
     m_nom_animal_label.set_message(thing_name);
     m_nom_animal_label.set_color(MARRONSOMBRE);*/




}

void Vertex::setarc_entrant(int numero_de_larc)
{
    m_in.push_back(numero_de_larc);
}
void Vertex::setarc_sortant(int numero_de_larc)
{
    m_out.push_back(numero_de_larc);
}

/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
   if(mouse_b)
    {
        //std::cout<<"afficher les caracteristiques\n";

        mouse_b = false;

    }



    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( patch::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update(int *x, int *y,bool *z)
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();



  /*   if (m_interface->m_bouton1.clicked())
     {
         *x = m_interface->getidx();
     }*/
}
int VertexInterface::getidx()
{
    return m_idx;
}


/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( patch::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h, std::string nom)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    /*  m_top_box.add_child(m_tool_box);
      m_tool_box.set_dim(80,720);
      m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
      m_tool_box.set_bg_color(ROUGE);*/

    m_top_box.add_child(m_main_box);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_pic_name(nom); /*

    ///boite à boutons
    m_tool_box.add_child(m_boite_boutons);
    m_boite_boutons.set_dim(75, 175);
    m_boite_boutons.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_boite_boutons.set_bg_color(GRISSOMBRE);

    /// bouton1
    m_boite_boutons.add_child(m_bouton1);
    m_bouton1.set_frame(0,0,78,44);
    m_bouton1.set_bg_color(BLEU);

    m_bouton1.add_child(m_bouton1_label);
    m_bouton1_label.set_message("SAUVER");


    /// bouton 2
    m_boite_boutons.add_child(m_bouton2);
    m_bouton2.set_frame(0,45,78,44);
    m_bouton2.set_bg_color(ROUGESOMBRE);

    m_bouton2.add_child(m_bouton2_label);
    m_bouton2_label.set_message("CHANGER");

    /// bouton 3
    m_boite_boutons.add_child(m_bouton3);
    m_bouton3.set_frame(0,90,78,44);
    m_bouton3.set_bg_color(BLEU);

    m_bouton3.add_child(m_bouton3_label);
    m_bouton3_label.set_message("+ ARETE");


    /// bouton 4
    m_boite_boutons.add_child(m_bouton4);
    m_bouton4.set_frame(0,135,78,44);
    m_bouton4.set_bg_color(ROUGESOMBRE);

    m_bouton4.add_child(m_bouton4_label);
    m_bouton4_label.set_message("EXIT");

    ///bouton 5
    m_boite_boutons.add_child(m_bouton5);
    m_bouton5.set_frame(0,179,78,44);
    m_bouton5.set_bg_color(BLEU);

    m_bouton5.add_child(m_bouton5_label);
    m_bouton5_label.set_message("+ SOMMET");


    ///bouton 6
    m_boite_boutons.add_child(m_bouton6);
    m_bouton6.set_frame(0,223,78,44);
    m_bouton6.set_bg_color(ROUGESOMBRE);

    m_bouton6.add_child(m_bouton6_label);
    m_bouton6_label.set_message("FORT C");

    ///bouton 7
    m_boite_boutons.add_child(m_bouton7);
    m_bouton7.set_frame(0,267,78,44);
    m_bouton7.set_bg_color(BLEU);

    m_bouton7.add_child(m_bouton7_label);
    m_bouton7_label.set_message("k C");*/


}


void Graph::recuperation(std::string nom1, std::string nom2, std::vector<Vertex>& mainVertices)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600, nom2);

    std::string n = nom1 + ".txt" ;

    std::ifstream fichier(n);

    if(fichier)
    {

        int v1 = 0;
        Vertex v;
        unsigned int idx, x,y;

        fichier >> v1;
        for(int i = 0 ; i < v1 ; i++)

        {
            fichier >> idx >>x>>y;
            //fichier >> x;
           // fichier >>  y;
            add_interfaced_vertex(idx, x, y);
            mainVertices.push_back(v);


            mainVertices[i].posx=x;
            mainVertices[i].posy=y;
            mainVertices[i].idx=idx;

        }
    }
    else
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;


}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(std::string nom)
{
    m_compteur ++;

    int *x = new int;
    int *y = new int;
    bool *z = new bool;
    *y = -1;
    *x = -1;
    *z = false;
    if (!m_interface)
        return;

/* for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
   {
        if(mouse_b)
        {
            std::cout<<"afficher les caracteristiques "<<m_vertices[it->first].getvalue()<<std::endl;
            mouse_b = false;
        }
    }*/

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update(x, y, z);
    for (auto &elt : m_edges)
        elt.second.post_update();

    /// TOUCHES CLAVIER
    if (key[KEY_B])
    {
        sauvegarde(m_vertices,nom);
    }
   /*    if (key[KEY_Q])
    {
          for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
    {
        m_vertices[it->first].setValue(it->first);
    }
    //key[KEY_Q]=false;
    }*/

    /// BOUTONS


    delete x;
    delete y;

    delete z;




       if(mouse_b&1 && 21 < mouse_x &&  mouse_x < 45 && 357< mouse_y && mouse_y < 378 )///graphe1
        {
            std::cout <<"je suis sur le sommet 1\n";
        }
        else if(mouse_b&1 && 46 < mouse_x &&  mouse_x < 69 && 517< mouse_y && mouse_y < 537 )///graphe1
        {
            std::cout <<"je suis sur le sommet 2\n";
        }





        for (auto &elt : m_vertices)
        {
           // if (MOUSE_CURSOR_ALLEGRO < m_vertices[it->first].pos_x )

            //if (m_top_box)

            /*
            m_top_box.set_pos(x, y);
            m_top_box.set_dim(11,11);
            */
        }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, int x, int y )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(0, vi);
}

void Graph::sauvegarde(std::map<int, Vertex> m_vertices, std::string nom)
{
    std::string buff;


    std::ofstream fichier(nom+".txt",std::ios::out|std::ios::trunc);

    std::map<int, Vertex>::iterator it;
    //std::map<int, Edge>::iterator it1;

    fichier << m_vertices.size()<<std::endl;
    //fichier << m_edges.size()  << std::endl;


    for(it = m_vertices.begin(); it != m_vertices.end(); it++)
        fichier<<it->first<<" "
               << m_vertices[it->first].m_interface->m_top_box.get_posx()
               <<" "<<m_vertices[it->first].m_interface->m_top_box.get_posy() <<  std::endl;

    fichier.close();
}

/*Graph::retourPositions()
{

    for(it = m_vertices.begin(); it != m_vertices.end(); it++)
    {
        if
        m_vertices[it->first].m_interface->m_top_box.get_posx()
        m_vertices[it->first].m_interface->m_top_box.get_posy()
    }


}*/


void Graph::clear_map()
{
    m_vertices.clear();
    m_edges.clear();
}

void Graph::credits()
{
     m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600, "credits.jpg");
}

