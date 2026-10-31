def knowledge_representation():
    """Demonstrate knowledge representation using facts."""

    knowledge_base = {
        "Name": "Aman",
        "Age": 20,
        "Occupation": "Student",
        "Studies": "Computer Science",
        "University": "DAVV"
    }

    print("Knowledge Base")
    print("--------------------")

    for key, value in knowledge_base.items():
        print(f"{key}: {value}")

    print("\nKnowledge Query")

    query = "Occupation"

    if query in knowledge_base:
        print(f"{query}: {knowledge_base[query]}")
    else:
        print("Information not found.")


if __name__ == "__main__":
    knowledge_representation()