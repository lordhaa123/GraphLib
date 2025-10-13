#pragma GCC optimize("O3")
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../include/graph.hpp"

TEST_CASE("Pathfinding Algorithms", "[pathfinding]") {
    Graph<std::string, int> g(false);
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addNode("E");

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 3);
    g.addEdge("B", "D", 5);
    g.addEdge("C", "D", 1);
    g.addEdge("C", "E", 4);
    g.addEdge("D", "E", 1);

    SECTION("Uniform Cost Search") {
        std::vector<std::string> path = g.uniformCostSearch("A", "E");
        std::vector<std::string> expected_path = {"A", "C", "D", "E"};
        REQUIRE(path == expected_path);
    }

    SECTION("A* Search") {
        auto heuristic = [](const std::string& a, const std::string& b) -> double {
            // A simple heuristic for demonstration
            if (a == "A" && b == "E") return 4.0;
            if (a == "C" && b == "E") return 2.0;
            if (a == "D" && b == "E") return 1.0;
            return 0.0;
        };

        std::vector<std::string> path = g.aStarSearch("A", "E", heuristic);
        std::vector<std::string> expected_path = {"A", "C", "D", "E"};
        REQUIRE(path == expected_path);
    }

    SECTION("Exception Handling for addEdge") {
        Graph<std::string, int> g_exc(true);
        g_exc.addNode("OnlyNode");
        REQUIRE_THROWS_AS(g_exc.addEdge("OnlyNode", "NonExistent", 1), std::out_of_range);
        REQUIRE_THROWS_AS(g_exc.addEdge("NonExistent", "OnlyNode", 1), std::out_of_range);
    }
}