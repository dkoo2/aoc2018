#include "track.h"

#include <cassert>
#include <iostream>
#include <set>
#include <span>
#include <string>
#include <vector>

namespace aoc2018 {

namespace {

Type ToType(const std::string& s) {
    if (s == " ") {
        return Type::Empty;
    }
    if (s == "\\") {
        return Type::LRCurve;
    }
    if (s == "/") {
        return Type::RLCurve;
    }
    if (s == "-") {
        return Type::Horizontal;
    }
    if (s == "|") {
        return Type::Vertical;
    }
    if (s == "+") {
        return Type::Intersection;
    }
    if (s == ">" || s == "<") {
        return Type::Horizontal;
    }
    if (s == "^" || s == "v") {
        return Type::Vertical;
    }

    assert(false);
    return Type::Empty;
}

bool IsCart(std::string_view s) {
    return s == ">" || s == "<" || s == "^" || s == "v";
}

Position NewPosition(const Position& cpos, const Direction cur_dir) {
    switch (cur_dir) {
        case Direction::Left:
            return {cpos.row, cpos.col - 1};
        case Direction::Right:
            return {cpos.row, cpos.col + 1};
        case Direction::Up:
            return {cpos.row - 1, cpos.col};
        case Direction::Down:
            return {cpos.row + 1, cpos.col};
    }
}

Direction NewDirForTypeAndDir(const Direction curr_dir, const Type next) {
    if (next == Type::LRCurve) {
        switch (curr_dir) {
            case Direction::Left:
                return Direction::Up;
            case Direction::Right:
                return Direction::Down;
            case Direction::Up:
                return Direction::Left;
            case Direction::Down:
                return Direction::Right;
        }
    }
    assert(next == Type::RLCurve);
    switch (curr_dir) {
        case Direction::Left:
            return Direction::Down;
        case Direction::Right:
            return Direction::Up;
        case Direction::Up:
            return Direction::Right;
        case Direction::Down:
            return Direction::Left;
    }
}

Direction NewDirForIntersection(const Direction curr_dir,
                                const IntersectionHandle ih) {
    switch (ih) {
        case IntersectionHandle::Left:
            switch (curr_dir) {
                case Direction::Left:
                    return Direction::Down;
                case Direction::Right:
                    return Direction::Up;
                case Direction::Up:
                    return Direction::Left;
                case Direction::Down:
                    return Direction::Right;
            }
        case IntersectionHandle::Straight:
            return curr_dir;
        case IntersectionHandle::Right:
            switch (curr_dir) {
                case Direction::Left:
                    return Direction::Up;
                case Direction::Right:
                    return Direction::Down;
                case Direction::Up:
                    return Direction::Right;
                case Direction::Down:
                    return Direction::Left;
            }
    }
}

}  // namespace

Cart::Cart(Position position, std::string_view initial_dir)
    : position_(position) {
    if (initial_dir == ">") {
        dir_ = Direction::Right;
    }
    if (initial_dir == "<") {
        dir_ = Direction::Left;
    }
    if (initial_dir == "^") {
        dir_ = Direction::Up;
    }
    if (initial_dir == "v") {
        dir_ = Direction::Down;
    }
}

void Cart::increment_intersection() {
    switch (next_intersection_) {
        case IntersectionHandle::Left:
            next_intersection_ = IntersectionHandle::Straight;
            break;
        case IntersectionHandle::Straight:
            next_intersection_ = IntersectionHandle::Right;
            break;
        case IntersectionHandle::Right:
            next_intersection_ = IntersectionHandle::Left;
            break;
    }
}

Track::Track(std::span<const std::string> paths) {
    track_.reserve(paths.size());
    for (int i = 0; i < paths.size(); ++i) {
        std::vector<Type> row;
        row.reserve(paths[i].size());
        for (int j = 0; j < paths[i].size(); ++j) {
            row.push_back(ToType(paths[i].substr(j, 1)));
            if (IsCart(paths[i].substr(j, 1))) {
                carts_.emplace_back(Position{i, j}, paths[i].substr(j, 1));
            }
        }
        track_.push_back(std::move(row));
    }
}

std::optional<Position> Track::CartsCollided() const {
    std::set<Position> locations;
    for (const Cart& c : carts_) {
        const Position& cpos = c.position();
        if (locations.contains(cpos)) {
            return cpos;
        }
        locations.insert(cpos);
    }
    return std::nullopt;
}

std::optional<Position> Track::RunOnce() {
    std::sort(carts_.begin(), carts_.end(),
              [](const Cart& lhs, const Cart& rhs) {
                  return lhs.position() < rhs.position();
              });
    for (Cart& cart : carts_) {
        const Position& cpos = cart.position();
        const Direction cdir = cart.dir();
        const Position new_pos = NewPosition(cpos, cdir);
        cart.set_position(new_pos);
        const std::optional<Position> maybe_collision = CartsCollided();
        if (maybe_collision.has_value()) {
            return maybe_collision;
        }
        switch (track_[new_pos.row][new_pos.col]) {
            case Type::Horizontal:
            case Type::Vertical:
                break;
            case Type::Intersection: {
                IntersectionHandle next = cart.intersection_handle();
                cart.set_dir(NewDirForIntersection(cdir, next));
                cart.increment_intersection();
            } break;
            case Type::LRCurve:
            case Type::RLCurve:
                cart.set_dir(NewDirForTypeAndDir(
                    cdir, track_[new_pos.row][new_pos.col]));
                break;
            case Type::Empty:
                assert(false);
                break;
        }
    }
    return std::nullopt;
}

void Track::KillCollisions(const Position& loc) {
    int count = 0;
    for (Cart& c : carts_) {
        if (!c.live()) continue;
        if (loc == c.position()) {
            ++count;
        }
        if (count > 1) {
            break;
        }
    }
    if (count > 1) {
        for (Cart& c : carts_) {
            if (loc == c.position()) {
                c.kill();
            }
        }
    }
}

void Track::RunOnceAndSquashCollisions() {
    std::sort(carts_.begin(), carts_.end(),
              [](const Cart& lhs, const Cart& rhs) {
                  return lhs.position() < rhs.position();
              });
    for (Cart& cart : carts_) {
        if (!cart.live()) continue;
        const Position& cpos = cart.position();
        const Direction cdir = cart.dir();
        const Position new_pos = NewPosition(cpos, cdir);
        cart.set_position(new_pos);
        KillCollisions(new_pos);

        // If it got squashed, then skip remaining work.
        if (!cart.live()) continue;
        const Type t = track_[new_pos.row][new_pos.col];
        switch (t) {
            case Type::Horizontal:
            case Type::Vertical:
                break;
            case Type::Intersection: {
                IntersectionHandle next = cart.intersection_handle();
                cart.set_dir(NewDirForIntersection(cdir, next));
                cart.increment_intersection();
            } break;
            case Type::LRCurve:
            case Type::RLCurve:
                cart.set_dir(NewDirForTypeAndDir(cdir, t));
                break;
            case Type::Empty:
                assert(false);
                break;
        }
    }
}

Position Track::FirstCollision() {
    for (;;) {
        const std::optional<Position> maybe_collision = RunOnce();
        if (maybe_collision.has_value()) {
            return *maybe_collision;
        }
    }
}

Position Track::LastRemaining() {
    for (;;) {
        int live = 0;
        Position pos = {-1, -1};
        RunOnceAndSquashCollisions();
        std::vector<Cart> live_carts;
        live_carts.reserve(carts_.size());
        for (Cart& c : carts_) {
            if (!c.live()) continue;
            ++live;
            pos = c.position();
            live_carts.push_back(std::move(c));
        }
        if (live == 1) return pos;
        carts_ = std::move(live_carts);
    }
}

}  // namespace aoc2018