#include <iostream>
#include <optional>
#include <span>
#include <string>
#include <utility>
#include <vector>

namespace aoc2018 {

enum class Type {
    Empty,
    LRCurve,  // "\"
    RLCurve,  // "/"
    Horizontal,
    Vertical,
    Intersection,
};

enum class Direction {
    Left,
    Right,
    Up,
    Down,
};

enum class IntersectionHandle {
    Left = 0,
    Straight = 1,
    Right = 2,
};

struct Position {
    int row;
    int col;

    auto operator<=>(const Position&) const = default;
};

class Cart {
   public:
    Cart(Position position, std::string_view initial_dir);

    const Position& position() const { return position_; }
    Direction dir() const { return dir_; }
    IntersectionHandle intersection_handle() const {
        return next_intersection_;
    }

    void set_position(const Position& p) { position_ = p; }
    void set_dir(Direction dir) { dir_ = dir; }
    void increment_intersection();

    bool live() const { return live_; }
    void kill() { live_ = false; }

   private:
    bool live_ = true;
    Position position_;
    Direction dir_;
    IntersectionHandle next_intersection_ = IntersectionHandle::Left;
};

class Track {
   public:
    explicit Track(std::span<const std::string> paths);

    // Part 1.
    Position FirstCollision();

    // Part 2.
    Position LastRemaining();

   private:
    // Part 1 helpers.
    std::optional<Position> RunOnce();
    std::optional<Position> CartsCollided() const;

    // Part 2 helpers.
    void RunOnceAndSquashCollisions();
    void KillCollisions(const Position& loc);

    std::vector<std::vector<Type>> track_;
    std::vector<Cart> carts_;
};

}  // namespace aoc2018
