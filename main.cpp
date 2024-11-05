#include <iostream>
#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef CGAL::Voronoi_diagram_2<DT> Voronoi;
typedef K::Point_2 Point;

int main() {
    // Input: number of points and the points themselves
    int n;
    std::cout << "Enter the number of points (plants): ";
    std::cin >> n;
    std::vector<Point> points;

    std::cout << "Enter the points in the form (x,y) for each plant location:\n";
    for (int i = 0; i < n; ++i) {
        double x, y;
        char ch;
        std::cin >> ch >> x >> ch >> y >> ch; // Read format (x,y)
        points.push_back(Point(x, y));
    }

    // Constructing the Voronoi Diagram
    DT dt;
    dt.insert(points.begin(), points.end());
    Voronoi voronoi(dt);

    // Output Voronoi cells as polygons
    int polygonIndex = 1;
    std::cout << "Voronoi Polygons (each polygon is a list of boundary points):\n";
    for (auto vit = voronoi.vertices_begin(); vit != voronoi.vertices_end(); ++vit) {
        std::cout << "Polygon " << polygonIndex++ << ": ";
        auto circulator = voronoi.incident_edges(vit), done = circulator;
        do {
            if (!dt.is_infinite(circulator)) {
                auto segment = dt.segment(circulator);
                std::cout << "(" << segment.source().x() << ", " << segment.source().y() << ") ";
            }
        } while (++circulator != done);
        std::cout << std::endl;
    }

    return 0;
}

