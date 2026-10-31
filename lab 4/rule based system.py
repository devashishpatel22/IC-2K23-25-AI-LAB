def rule_based_system():
    """Demonstrate a simple IF-THEN rule-based system."""

    facts = {
        "has_wings",
        "has_feathers",
        "can_lay_eggs"
    }

    rules = [
        ({"has_wings", "has_feathers"}, "is_bird"),
        ({"is_bird", "can_lay_eggs"}, "is_likely_bird_species")
    ]

    print("Initial Facts:", facts)

    changed = True

    while changed:
        changed = False

        for conditions, conclusion in rules:
            if conditions.issubset(facts) and conclusion not in facts:
                facts.add(conclusion)
                print("Rule Fired:", conclusion)
                changed = True

    print("\nFinal Knowledge Base:")
    for fact in sorted(facts):
        print(fact)


if __name__ == "__main__":
    rule_based_system()