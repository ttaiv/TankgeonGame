#include "include/Ordnance.hpp"

// Ordnance::Ordnance(sf::Vector2f initial_position) : pos_(initial_position) {}

Ordnance::Ordnance() : is_active_(true) {}

bool Ordnance::IsActive() const { return is_active_; }
void Ordnance::SetInactive() { is_active_ = false; }
void Ordnance::SetActive() { is_active_ = true; }