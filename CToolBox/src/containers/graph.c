/**
 * \file 	graph.c
 * \brief 	Gestion d'un graph
 * \author 	Loky
 */

#include <stdbool.h>
#include <toolbox/memory.h>
#include <containers/graph.h>

#define INFINITY -1

struct edge_t_
{
	unsigned long id;
	double weight;
	node_t *from;
	node_t *to;
};

static void graph_t_init(graph_t*);
static void way_t_init(way_t*);
void way_t_destroy(way_t*);

static void way_t_init(way_t* this)
{

	this->destroy = way_t_destroy;
}

/**
 * Initialise le chemin
 * \return le chemin
 */
way_t* way_t_create()
{
	way_t *this;
	MALLOC(this, way_t, 1);
	way_t_init(this);
	return this;

}

void way_t_destroy(way_t* this)
{

	if (this->node_list != NULL)
		FREE(this->node_list);
	FREE(this);
}

void graph_t_destroy(graph_t*);
void graph_t_clear(graph_t*);

node_t* graph_t_add_node(graph_t*, void*);

void graph_t_add_undirected_edge(graph_t*, node_t*, node_t*);
void graph_t_add_directed_edge(graph_t*, node_t*, node_t*);
void graph_t_add_undirected_weighted_edge(graph_t*, node_t*, node_t*,
		const double);
void
graph_t_add_directed_weighted_edge(graph_t*, node_t*, node_t*, const double);

void graph_t_dijkstra(const graph_t*, const node_t*, const node_t*, way_t*);
_Bool graph_t_connexe_node(const graph_t* this, const node_t*, const node_t*);
_Bool graph_t_connexe(const graph_t* this);

void graph_t_remove_edge(const graph_t*, node_t*, node_t*);
void graph_t_remove_directed_edge(const graph_t*, const node_t*, const node_t*);
void graph_t_remove_node(const graph_t*, node_t*);

void graph_t_export_undirected(const graph_t*, FILE*);
void graph_t_export_directed(const graph_t*, FILE*);
void graph_t_export_undirected_weighted(const graph_t*, FILE*);
void graph_t_export_directed_weighted(const graph_t*, FILE*);

static void graph_t_init(graph_t* this)
{

	this->destroy = graph_t_destroy;
	this->clear = graph_t_clear;

	this->add_node = graph_t_add_node;

	this->add_undirected_edge = graph_t_add_undirected_edge;
	this->add_directed_edge = graph_t_add_directed_edge;
	this->add_undirected_weighted_edge = graph_t_add_undirected_weighted_edge;
	this->add_directed_weighted_edge = graph_t_add_directed_weighted_edge;

	this->dijkstra = graph_t_dijkstra;
	this->connexe = graph_t_connexe;
	this->connexe_node = graph_t_connexe_node;

	this->remove_edge = graph_t_remove_edge;
	this->remove_directed_edge = graph_t_remove_directed_edge;
	this->remove_node = graph_t_remove_node;

	this->export_undirected = graph_t_export_undirected;
	this->export_directed = graph_t_export_directed;
	this->export_undirected_weighted = graph_t_export_undirected_weighted;
	this->export_directed_weighted = graph_t_export_directed_weighted;
}

void graph_t_destroy(graph_t* this)
{
	graph_t_clear(this);
	this->node_list->destroy(this->node_list);
	FREE(this);
}
void graph_t_clear(graph_t* this)
{
	list_item_t *item = this->node_list->first;
	while (HAS_NEXT_ITEM(item))
	{
		((node_t*) item->data)->edge_in->destroy(
				(((node_t*) item->data)->edge_in));
		((node_t*) item->data)->edge_out->destroy(
				(((node_t*) item->data)->edge_out));
		NEXT_ITEM(item);
	}
	this->node_list->clear(this->node_list);
	this->node_count = 0;
	this->edge_count = 0;
}

node_t* graph_t_add_node(graph_t* this, void* data)
{

	node_t *node;
	MALLOC(node, node_t, 1);
	node->data = data;
	node->edge_in = list_t_create();
	node->edge_out = list_t_create();
	node->id = this->node_count++;
	this->node_list->push_back(this->node_list, node);
	return node;
}

void graph_t_add_undirected_edge(graph_t* this, node_t* node1, node_t* node2)
{
	graph_t_add_undirected_weighted_edge(this, node1, node2, 1);
}
void graph_t_add_directed_edge(graph_t* this, node_t* from, node_t* to)
{
	graph_t_add_directed_weighted_edge(this, from, to, 1);
}
void graph_t_add_undirected_weighted_edge(graph_t* this, node_t* node1,
		node_t* node2, const double weight)
{
	graph_t_add_directed_weighted_edge(this, node1, node2, weight);
	graph_t_add_directed_weighted_edge(this, node2, node1, weight);
}
void graph_t_add_directed_weighted_edge(graph_t* this, node_t* from,
		node_t* to, const double weight)
{
	edge_t * edge1, *edge2;
	MALLOC(edge1, edge_t, 1);
	edge1->id = this->edge_count++;
	edge1->from = from;
	edge1->to = to;
	edge1->weight = weight;
	from->edge_out->push_back(from->edge_out, edge1);
	MALLOC(edge2, edge_t, 1);
	edge2->id = this->edge_count;
	edge2->from = from;
	edge2->to = to;
	edge2->weight = weight;
	to->edge_in->push_back(to->edge_in, edge2);
}

void graph_t_remove_edge(const graph_t* this, node_t* node1, node_t* node2)
{
	graph_t_remove_directed_edge(this, node1, node2);
	graph_t_remove_directed_edge(this, node2, node1);
}
void graph_t_remove_directed_edge(const graph_t* this, const node_t* from,
		const node_t* to)
{
	if (!from->edge_out->empty(from->edge_out))
	{
		int i = 0;
		list_item_t *item = from->edge_out->first;
		while (HAS_NEXT_ITEM(item))
		{
			if (((edge_t*) item->data)->to == to)
			{
				from->edge_out->erase(from->edge_out, i);
				return;
			}
			i++;
			NEXT_ITEM(item);
		}
	}
}
void graph_t_remove_node(const graph_t* this, node_t* node)
{
	int i = 0;
	list_item_t *item = this->node_list->first;
	while (HAS_NEXT_ITEM(item))
	{
		graph_t_remove_directed_edge(this, ((node_t*) item->data), node);
		NEXT_ITEM(item);
	}
	item = this->node_list->first;
	while (HAS_NEXT_ITEM(item))
	{
		if (((node_t*) item->data) == node)
		{
			node->edge_in->destroy(node->edge_in);
			node->edge_out->destroy(node->edge_out);
			this->node_list->erase(this->node_list, i);
			return;
		}
		i++;
		NEXT_ITEM(item);
	}
}

void write_edge(FILE* file, const node_t *node, const edge_t *edge,
		const _Bool directed, const _Bool weighted)
{
	fprintf(file, "%ld -", node->id);
	if (directed)
		fprintf(file, ">");
	else
		fprintf(file, "-");
	fprintf(file, "%ld", edge->to->id);
	if (weighted)
		fprintf(file, " [weight=%f]", edge->weight);
	fprintf(file, ";\n");
}

void write_edge_list(FILE* file, node_t *node, const _Bool directed,
		const _Bool weighted)
{
	if (!node->edge_out->empty(node->edge_out))
	{
		list_item_t *item = node->edge_out->first;
		while (HAS_NEXT_ITEM(item))
		{
			write_edge(file, node, (edge_t*) item->data, directed, weighted);
			NEXT_ITEM(item);
		}
	}
}

void write_graph(const graph_t* this, FILE* file, const _Bool directed,
		const _Bool weighted)
{
	if (!this->node_list->empty(this->node_list))
	{
		list_item_t *item = this->node_list->first;
		if (directed)
			fprintf(file, "digraph G {\n");
		else
			fprintf(file, "graph G {\n");
		while (HAS_NEXT_ITEM(item))
		{
			write_edge_list(file, (node_t*) item->data, directed, weighted);
			NEXT_ITEM(item);
		}

		fprintf(file, "}\n");
		fflush(file);
	}
}

void graph_t_export_undirected(const graph_t* this, FILE* file)
{
	write_graph(this, file, false, false);
}
void graph_t_export_directed(const graph_t* this, FILE* file)
{
	write_graph(this, file, true, false);
}
void graph_t_export_undirected_weighted(const graph_t* this, FILE* file)
{
	write_graph(this, file, false, true);
}
void graph_t_export_directed_weighted(const graph_t* this, FILE* file)
{
	write_graph(this, file, true, true);
}
typedef struct node_dijkstra_t_ node_dijkstra_t;
struct node_dijkstra_t_
{
	node_t *courrant;
	node_dijkstra_t* precedant;
	double parcouru;
};

#include <float.h>

_Bool empty(const graph_t* this, node_dijkstra_t**pas_encore_vu)
{
	int i = 0;
	for (; i < this->node_list->size; i++)
		if (pas_encore_vu[i] != NULL)
			return false;
	return true;
}

node_dijkstra_t* get_min_dist(const graph_t* this,
		node_dijkstra_t**pas_encore_vu)
{
	int i = 0, count=0;
	node_dijkstra_t* res = NULL;
	for (; i < this->node_list->size; i++)
	{
		if (res == NULL || (pas_encore_vu[i] != NULL
				&& pas_encore_vu[i]->parcouru < res->parcouru))
		{
			res = pas_encore_vu[i];
			count = i;
		}
	}
	pas_encore_vu[count] = NULL;
	return res;
}

node_dijkstra_t* get_node_dijkstra(const graph_t* this,
		node_dijkstra_t**noeuds, const node_t*node)
{
	int i = 0;
	for (; i < this->node_list->size; i++)
		if (noeuds[i]->courrant == node)
			return noeuds[i];
	return NULL;
}

void maj_poid(const graph_t* this, node_dijkstra_t ** noeuds,
		node_dijkstra_t*n1)
{
	list_item_t *item = n1->courrant->edge_out->first;
	while (HAS_NEXT_ITEM(item))
	{
		node_dijkstra_t* n2 = get_node_dijkstra(this, noeuds,
				((edge_t*) item->data)->to);
		double weight = n1->parcouru + ((edge_t*) item->data)->weight;
		if (n2 != NULL && n2->parcouru > weight)
		{
			n2->parcouru = weight;
			n2->precedant = n1;
		}
		NEXT_ITEM(item);
	}

}

int get_way_size(node_dijkstra_t* debut, node_dijkstra_t*fin, int count)
{
	if (fin == NULL)
		return 0;
	if (fin != debut)
		return get_way_size(debut, fin->precedant, count + 1);
	else
		return count + 1;
}

void get_way(node_t**res, node_dijkstra_t* debut, node_dijkstra_t*fin,
		int count)
{
	if (count >= 0)
	{
		res[count] = fin->courrant;
		get_way(res, debut, fin->precedant, count - 1);
	}
}
void graph_t_dijkstra(const graph_t* this, const node_t* from,
		const node_t* to, way_t* res)
{
	node_dijkstra_t ** noeuds;
	node_dijkstra_t* debut=NULL, *fin=NULL;
	int size;
	int i = 0;
	node_dijkstra_t**pas_encore_vu;
	list_item_t *item = this->node_list->first;
	MALLOC(noeuds, node_dijkstra_t*, this->node_list->size);
	MALLOC(pas_encore_vu, node_dijkstra_t*, this->node_list->size);

	while (HAS_NEXT_ITEM(item))
	{
		node_dijkstra_t* tmp;
		MALLOC(tmp, node_dijkstra_t, 1);
		tmp->courrant = item->data;
		tmp->precedant = NULL;
		if (item->data == from)
		{
			debut = tmp;
			debut->parcouru = 0;
		}
		else
			tmp->parcouru = DBL_MAX;

		if (item->data == to)
			fin = tmp;
		noeuds[i] = tmp;
		pas_encore_vu[i] = tmp;
		i++;
		NEXT_ITEM(item);
	}
	while (!empty(this, pas_encore_vu))
	{
		node_dijkstra_t *n1 = get_min_dist(this, pas_encore_vu);
		maj_poid(this, noeuds, n1);
	}
	size = get_way_size(debut, fin, 0);
	if (size != 0)
	{
		MALLOC(res->node_list, node_t*, size);
		get_way(res->node_list, debut, fin, size - 1);
		res->length = fin->parcouru;
	}
	else
	{
		res->node_list = NULL;
		res->length = INFINITY;
	}
	res->size = size;
	FREE(pas_encore_vu);
	for (size = 0; size < this->node_list->size; size++)
		FREE(noeuds[size]);
	FREE(noeuds);
}

_Bool connexe_node(node_t *item, const node_t* node)
{
	node_t *cur = (node_t*) item;
	list_item_t *item2 = cur->edge_out->first;
	if (cur == node)
		return true;
	cur->mark = true;

	while (HAS_NEXT_ITEM(item2))
	{
		if (!((node_t*) ((edge_t*) item2->data)->to)->mark)
		{
			if (connexe_node(((node_t*) ((edge_t*) item2->data)->to), node))
				return true;
		}
		NEXT_ITEM(item2);
	}
	return false;
}

_Bool graph_t_connexe_node(const graph_t* this, const node_t* from,
		const node_t* to)
{
	list_item_t *item = this->node_list->first;
	list_item_t *from_item = NULL;
	while (HAS_NEXT_ITEM(item))
	{
		if (from == ((node_t*) item->data))
			from_item = item;
		((node_t*) item->data)->mark = false;
		NEXT_ITEM(item);
	}

	return connexe_node((node_t*) from_item->data, to);

}

void connexe(node_t *item, const int nb)
{
	node_t *cur = (node_t*) item;
	list_item_t *item2 = cur->edge_out->first;
	cur->mark = true;

	while (HAS_NEXT_ITEM(item2))
	{
		if (!((node_t*) ((edge_t*) item2->data)->to)->mark)
			connexe(((node_t*) ((edge_t*) item2->data)->to), nb);
		NEXT_ITEM(item2);
	}
}

_Bool connexe_for_node(const graph_t* this, node_t *first)
{
	list_item_t *item = this->node_list->first;
	while (HAS_NEXT_ITEM(item))
	{
		((node_t*) item->data)->mark = false;
		NEXT_ITEM(item);
	}

	connexe(first, this->node_list->size);
	item = this->node_list->first;
	while (HAS_NEXT_ITEM(item))
	{
		if (!((node_t*) item->data)->mark)
			return false;
		NEXT_ITEM(item);
	}
	return true;
}

_Bool graph_t_connexe(const graph_t* this)
{
	list_item_t *item = this->node_list->first;
	while (HAS_NEXT_ITEM(item))
	{
		if (!connexe_for_node(this, (node_t*) item->data))
			return false;
		NEXT_ITEM(item);
	}
	return true;
}

/**
 * Initialise le graphe
 * \return le graphe
 */
graph_t* graph_t_create()
{
	graph_t *this;
	MALLOC(this, graph_t, 1);
	graph_t_init(this);
	this->node_list = list_t_create();
	this->node_count = 0;
	this->edge_count = 0;
	return this;
}
