#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include <map>
#include <string>
#include <memory>


#include "grman/grman.h"

/***************************************************
                    VERTEX
****************************************************/

class VertexInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;
//    friend class VertexInterface;

private :
public :
    /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
    /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
    /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

    // La boite qui contient toute l'interface d'un sommet
    grman::WidgetBox m_top_box;

    // Un slider de visualisation/modification de la valeur du sommet
    grman::WidgetVSlider m_slider_value;

    // Un label de visualisation de la valeur du sommet
    grman::WidgetText m_label_value;

    // Une image de "remplissage"
    grman::WidgetImage m_img;

    // Un label indiquant l'index du sommet
    grman::WidgetText m_label_idx;

    // Une boite pour le label pr�c�dent
    grman::WidgetText m_box_label_idx;

   // grman::WidgetText m_msg;
 //   grman::WidgetButton m_bouton1;

   // grman::WidgetBox m_nom_animal;
   // grman::WidgetText m_nom_animal_label;




    std::string m_thing;
//public :

    int m_idx;
    int m_x;
    int m_y;

    // Le constructeur met en place les �l�ments de l'interface
    // voir l'impl�mentation dans le .cpp
    VertexInterface(int idx, int x, int y);
    VertexInterface();
    int getidx();
    std::string getthing()
    {
        return m_thing;
    }

    void changement_de_couleur_sommet(int idx);
    void constructeur_default();

};


class Vertex
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

protected :


    /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
    std::vector<int> m_in;

    /// liste des indices des arcs partant du sommet : acc�s aux successeurs
    std::vector<int> m_out;

    /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
    double m_value;

    bool m_marque; /// Pour le BFS apparemment ...

    float m_K;

    /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
    std::shared_ptr<VertexInterface> m_interface = nullptr;

    // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
    // La ligne pr�c�dente est en gros �quivalent � la ligne suivante :
    // VertexInterface * m_interface = nullptr;



public:

    int posx;
    int posy;
    int idx;
    int numHydrant;
    std::string infosHydrant;
    int reseau;


    /// Les constructeurs sont � compl�ter selon vos besoin...
    /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
    Vertex (double value=0, VertexInterface *interface=nullptr) :
        m_value(value), m_interface(interface)  {  }

    /// Vertex �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
    /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
    /// Voir l'impl�mentation Graph::update dans le .cpp
    void pre_update();
    void post_update(int *x, int *y,bool *z);
    double getvalue()
    {
        return m_value;
    }
    void setValue(double value)
    {
        m_value=value;
         }
    void setarc_entrant(int numero_de_larc);
    void setarc_sortant(int numero_de_larc);
};



/***************************************************
                    EDGE
****************************************************/

class EdgeInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Edge;
    friend class Graph;

private :

    /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
    /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
    /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

    // Le WidgetEdge qui "contient" toute l'interface d'un arc
    grman::WidgetEdge m_top_edge;

    // Une boite pour englober les widgets de r�glage associ�s
    grman::WidgetBox m_box_edge;

    // Un slider de visualisation/modification du poids valeur de l'arc
    grman::WidgetVSlider m_slider_weight;

    // Un label de visualisation du poids de l'arc
    grman::WidgetText m_label_weight;

    grman::WidgetEdge m_test;

public :


    // Le constructeur met en place les �l�ments de l'interface
    // voir l'impl�mentation dans le .cpp
    EdgeInterface(Vertex& from, Vertex& to);
};


class Edge
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graph;
    friend class EdgeInterface;

private :
    /// indice du sommet de d�part de l'arc
    int m_from;

    /// indice du sommet d'arriv�e de l'arc
    int m_to;

    /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
    double m_weight;

    /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
    std::shared_ptr<EdgeInterface> m_interface = nullptr;


public:

int idx;
int id_vert1;
int id_vert2;
int reseau;
    /// Les constructeurs sont � compl�ter selon vos besoin...
    /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
    Edge (double weight=0, EdgeInterface *interface=nullptr) :
        m_weight(weight), m_interface(interface)  {  }

    /// Edge �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
    /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
    /// Voir l'impl�mentation Graph::update dans le .cpp
    void pre_update();
    void post_update();
};




/***************************************************
                    GRAPH
****************************************************/

class GraphInterface
{
    friend class Graph;

private :
public :
    /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
    /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
    /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

    /// La boite qui contient toute l'interface d'un graphe
    grman::WidgetBox m_top_box;

    /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
    grman::WidgetImage m_main_box;

    /// Dans cette boite seront ajout�s des boutons de contr�le etc...
    grman::WidgetBox m_tool_box;
    grman::WidgetBox m_boite_boutons;

    grman::WidgetButton m_bouton1;//cr�ation du bouton
    grman::WidgetText m_bouton1_label; //label associ�

    grman::WidgetButton m_bouton2;
    grman::WidgetText m_bouton2_label;

    grman::WidgetButton m_bouton3;
    grman::WidgetText m_bouton3_label;

    grman::WidgetButton m_bouton4;
    grman::WidgetText m_bouton4_label;

    grman::WidgetButton m_bouton5;
    grman::WidgetText m_bouton5_label;

    grman::WidgetButton m_bouton6;
    grman::WidgetText m_bouton6_label;

    grman::WidgetButton m_bouton7;
    grman::WidgetText m_bouton7_label;

    grman::WidgetButton m_bouton8;
    grman::WidgetText m_bouton8_label;

    // A compl�ter �ventuellement par des widgets de d�coration ou
    // d'�dition (boutons ajouter/enlever ...)

//public :

    // Le constructeur met en place les �l�ments de l'interface
    // voir l'impl�mentation dans le .cpp
    GraphInterface(int x, int y, int w, int h, std::string nom);
};


class Graph
{

    private :

        /// La "liste" des ar�tes
        std::map<int, Edge> m_edges;

        /// La liste des sommets
        std::map<int, Vertex> m_vertices;
        /// liste des sommets interfac�s
        std::map< int ,VertexInterface> m_interfacedVertices;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        int m_compteur = 0;
        bool m_test = false;


    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface)  {  }

        void add_interfaced_vertex(int idx, int x, int y );
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        /// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
        /// Voir impl�mentation dans le .cpp
        /// Cette m�thode est � enlever et remplacer par un syst�me
        /// de chargement de fichiers par exemple.
        void make_example();


        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        void update(std::string nom);
        void recuperation(std::string nom, std::string nom1, std::vector<Vertex>& mainVertices, std::vector<Edge>&mainEdges);
        void recuperation_bis(std::string nom);
        void sauvegarde(std::map<int, Vertex> m_vertices, std::string nom);
        void remplissagemap(std::string path);
        void test_remove_edge(int eidx);
        void enleversommet(int idx);
        int k_connexite();  /// renvoie le kmin= nbr de sommet minimale a enlever pour briser la connxite du graphe
        void clear_map();
        void add_edge();
        void kosaraju();
        void bfs();
        void composante_fortement_connexe();
        std::vector<int> BFS(); /// renvoie un vecteur contenant la compo connexe du graphe (attention il suppose que le graphe est entierement connexe)
        void ajoutsommet();
        float calcul_K(int x);
    float calcul_Coeff(int idx);
    void evol_pop();
    void forte_conexite();
    void sauvegarde_bis(std::map<int , Vertex>);
    void credits();
    void affichage_arette(int idx, int id_vert1, int id_vert2);




};


#endif // GRAPH_H_INCLUDED
