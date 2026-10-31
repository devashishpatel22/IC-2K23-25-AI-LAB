import networkx as nx
import matplotlib.pyplot as plt


def create_semantic_network():
    """Create and visualize a semantic network."""

    graph = nx.DiGraph()

    relationships = [
        ("Dog", "Animal", "is-a"),
        ("Cat", "Animal", "is-a"),
        ("Dog", "Bark", "can"),
        ("Cat", "Meow", "can"),
        ("Animal", "Living Thing", "is-a"),
        ("Dog", "Four Legs", "has"),
        ("Cat", "Four Legs", "has")
    ]

    for subject, obj, relation in relationships:
        graph.add_edge(subject, obj, relation=relation)

    print("Semantic Network Relationships:")

    for subject, obj, data in graph.edges(data=True):
        print(f"{subject} --{data['relation']}--> {obj}")

    pos = nx.spring_layout(graph, seed=42)

    nx.draw(
        graph,
        pos,
        with_labels=True,
        node_color="lightblue",
        node_size=2500,
        font_size=9,
        arrows=True
    )

    edge_labels = nx.get_edge_attributes(graph, "relation")
    nx.draw_networkx_edge_labels(
        graph, pos, edge_labels=edge_labels
    )

    plt.title("Semantic Network")
    plt.savefig("semantic_network.png")
    plt.show()


if __name__ == "__main__":
    create_semantic_network()