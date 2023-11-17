#include <SFML/Graphics.hpp>

class OBB // Oriented bounding box
{
public:
    sf::RectangleShape box;

    // Create an OBB from a transformed (i.e., scaled, rotated, and translated) sf::RectangleShape
    OBB(const sf::RectangleShape& rectangle)
    {
        box = rectangle;
    }

    // Check collision with another OBB
    bool collides(const OBB& other) const
    {
        sf::Transform t1 = box.getTransform();
        sf::Transform t2 = other.box.getTransform();

        std::vector<sf::Vector2f> axises;
        axises.push_back(normalize(getRotate(t1.transformPoint(box.getPoint(1)) - t1.transformPoint(box.getPoint(0)))));
        axises.push_back(normalize(getRotate(t1.transformPoint(box.getPoint(2)) - t1.transformPoint(box.getPoint(1)))));
        axises.push_back(normalize(getRotate(t2.transformPoint(other.box.getPoint(1)) - t2.transformPoint(other.box.getPoint(0)))));
        axises.push_back(normalize(getRotate(t2.transformPoint(other.box.getPoint(2)) - t2.transformPoint(other.box.getPoint(1)))));

        for (auto& axis : axises)
        {
            if (!overlap(project(axis), other.project(axis)))
                return false;
        }

        return true;
    }

private:
    sf::Vector2f getRotate(const sf::Vector2f& p) const
    {
        return sf::Vector2f(-p.y, p.x);
    }

    sf::Vector2f normalize(const sf::Vector2f& p) const
    {
        float l = std::sqrt(p.x * p.x + p.y * p.y);
        return sf::Vector2f(p.x / l, p.y / l);
    }

    std::pair<float, float> project(const sf::Vector2f& axis) const
    {
        sf::Transform t = box.getTransform();

        float dotp = axis.x * t.transformPoint(box.getPoint(0)).x + axis.y * t.transformPoint(box.getPoint(0)).y;
        std::pair<float, float> minmax(dotp, dotp);

        for (std::size_t i = 1; i < box.getPointCount(); ++i)
        {
            dotp = axis.x * t.transformPoint(box.getPoint(i)).x + axis.y * t.transformPoint(box.getPoint(i)).y;
            minmax.first = std::min(minmax.first, dotp);
            minmax.second = std::max(minmax.second, dotp);
        }

        return minmax;
    }

    bool overlap(const std::pair<float, float>& a, const std::pair<float, float>& b) const
    {
        return a.first <= b.second && a.second >= b.first;
    }
};
