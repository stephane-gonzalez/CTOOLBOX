/**
 * \file 	graph.h
 * \brief 	Gestion d'un graph
 * \author 	Loky
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
#include <containers/list.h>

/**
 * Type arc
 */
typedef struct edge_t_ edge_t;

/**
 * \brief Definition d'un noeud
 */
typedef struct node_t
{
	/**
	 * Identifiant d'un noeud
	 */
	unsigned long id;

	/**
	 * Donnée d'un noeud
	 */
	void* data;

	/**
	 * Arc en sortie
	 */
	list_t* edge_in;

	/**
	 * Arc en entree
	 */
	list_t* edge_out

	/**
	 * Markeur (private)
	 */;
	_Bool mark;
} node_t;

/**
 * \brief Gestion des chemins dans un graphe
 */
typedef struct way_t
{
	/**
	 * Liste de noeuds
	 */
	node_t**node_list;

	/**
	 * Longueur
	 */
	double length;

	/**
	 * Nombre de noeuds
	 */
	size_t size;

	/**
	 * Destructeur
	 * \param way_t le chemin
	 */
	void (*destroy)(struct way_t*);
} way_t;

way_t* way_t_create();

/**
 * \brief Gestion d'un graph
 */
typedef struct graph_t
{
	/**
	 * Liste des noeuds
	 */
	list_t * node_list;

	/**
	 * Compteur pour les identifiants de noeuds (private)
	 */
	unsigned long node_count;

	/**
	 * Compteur pour les identifiants d'arc (private)
	 */
	unsigned long edge_count;

	/**
	 * Destructeur
	 * \param graph_t le graphe
	 */
	void (*destroy)(struct graph_t*);

	/**
	 * Vide le graphe
	 * \param graph_t le graphe
	 */
	void (*clear)(struct graph_t*);

	/**
	 * Ajoute un noeud
	 * \param graph_t le graphe
	 * \param void* la donnée
	 * \return le noeud insere
	 */
	node_t* (*add_node)(struct graph_t*, void*);

	/**
	 * Ajoute un arc non oriente entre 2 noeuds
	 * \param graph_t le graphe
	 * \param le premier noeud
	 * \param le second noeud
	 */
	void (*add_undirected_edge)(struct graph_t*, node_t*, node_t*);
	/**
	 * Ajoute un arc oriente entre 2 noeuds
	 * \param graph_t le graphe
	 * \param le premier noeud
	 * \param le second noeud
	 */
	void (*add_directed_edge)(struct graph_t*, node_t*, node_t*);

	/**
	 * Ajoute un arc non oriente avec poid entre 2 noeuds
	 * \param graph_t le graphe
	 * \param le premier noeud
	 * \param le second noeud
	 * \param double le poid
	 */
	void (*add_undirected_weighted_edge)(struct graph_t*, node_t*, node_t*,
			const double);

	/**
	 * Ajoute un arc  oriente avec poid entre 2 noeuds
	 * \param graph_t le graphe
	 * \param le premier noeud
	 * \param le second noeud
	 * \param double le poid
	 */
	void (*add_directed_weighted_edge)(struct graph_t*, node_t*, node_t*,
			const double);

	/**
	 * recherche du plus court chemin
	 * \param graph_t le graphe
	 * \param node_t le premier noeud
	 * \param node_t le dernier noeud
	 *
	 */
	void (*dijkstra)(const struct graph_t*, const node_t*, const node_t*,
			way_t*);

	/**
	 * retourne si il y a une connexite entiére dans le graphe
	 * \param graph_t le graphe
	 * \return vrai si le graphe est connese faux sinon
	 *
	 */
	_Bool (*connexe)(const struct graph_t*);

	/**
	 * retourne si il y a une connexite entre deux noeud
	 *
	 * \param graph_t le graphe
	 * \param node_t le premier noeud
	 * \param node_t le dernier noeud
	 * \return vrai si le graphe est connese faux sinon
	 *
	 */
	_Bool (*connexe_node)(const struct graph_t*, const node_t*, const node_t*);

	/**
	 * Supprime un arc non oriente dans le graphe
	 * \param graph_t le graphe
	 * \param node_t le premier noeud
	 * \param node_t le dernier noeud
	 *
	 */
	void (*remove_edge)(const struct graph_t*, node_t*, node_t*);

	/**
	 * Supprime un arc oriente dans le graphe
	 * \param graph_t le graphe
	 * \param node_t le premier noeud
	 * \param node_t le dernier noeud
	 *
	 */
	void (*remove_directed_edge)(const struct graph_t*, const node_t*,
			const node_t*);
	/**
	 * Supprime un noeud dans le graphe
	 * \param graph_t le graphe
	 * \param node_t le noeud
	 *
	 */
	void (*remove_node)(const struct graph_t*, node_t*);

	/**
	 * Export au format dot sous forme de graphe non oriente
	 * \param graph_t le graphe
	 * \param FILE le fichier le graphe
	 *
	 */
	void (*export_undirected)(const struct graph_t*, FILE*);

	/**
	 * Export au format dot sous forme de graphe oriente
	 * \param graph_t le graphe
	 * \param FILE le fichier le graphe
	 *
	 */
	void (*export_directed)(const struct graph_t*, FILE*);

	/**
	 * Export au format dot sous forme de graphe non oriente avec poid
	 * \param graph_t le graphe
	 * \param FILE le fichier le graphe
	 *
	 */
	void (*export_undirected_weighted)(const struct graph_t*, FILE*);

	/**
	 * Export au format dot sous forme de graphe oriente avec poid
	 * \param graph_t le graphe
	 * \param FILE le fichier le graphe
	 *
	 */
	void (*export_directed_weighted)(const struct graph_t*, FILE*);

} graph_t;

graph_t* graph_t_create();

#ifdef __cplusplus
}
#endif

#endif /* GRAPH_H_ */
