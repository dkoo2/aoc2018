#include <set>
#include <span>
#include <string>
#include <utility>
#include <vector>
#include <map>

namespace aoc2018 {

class Point {
   public:
    Point(int px, int py, int vx, int vy)
        : px_(px), py_(py), vx_(vx), vy_(vy) {}

    int px() const { return px_; }
    int py() const { return py_; }

    void RunOnce();

   private:
    int px_;
    int py_;
    int vx_;
    int vy_;
};

class Grid {
   public:
    explicit Grid(std::span<const std::string> lines);

    void RunOnce();

    void Print() const;

    int RunUntilConnected();

   private:
    bool Connected() const;
    std::vector<Point> points_;
    std::set<std::pair<int, int>> points_set_;
};

}  // namespace aoc2018