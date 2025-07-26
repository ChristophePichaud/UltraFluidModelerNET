#include "pch.h"
#include "UFMCore\GraphLayoutEngine.h"

GraphNode::GraphNode(shared_ptr<CElement> el, PointF pos)
    : element(el), position(pos), velocity({ 0, 0 }), accumulatedForce({ 0, 0 }) {
}

void GraphNode::ApplyForce(const PointF& force) {
    accumulatedForce.X += force.X;
    accumulatedForce.Y += force.Y;
}

void GraphNode::UpdatePosition(float damping) {
    velocity.X = accumulatedForce.X * damping;
    velocity.Y = accumulatedForce.Y * damping;
    position.X += velocity.X;
    position.Y += velocity.Y;
    accumulatedForce = { 0, 0 };
}

GraphEdge::GraphEdge(shared_ptr<GraphNode> a, shared_ptr<GraphNode> b)
    : from(a), to(b) {
}

void GraphLayoutEngine::AddElement(shared_ptr<CElement> el) {
    PointF initial = { static_cast<float>(rand() % 800 + 100), static_cast<float>(rand() % 600 + 100) };
    nodes.push_back(make_shared<GraphNode>(el, initial));
}

void GraphLayoutEngine::AddConnector(shared_ptr<CElement> from, shared_ptr<CElement> to) {
    auto a = FindNode(from);
    auto b = FindNode(to);
    if (a && b) edges.emplace_back(a, b);
}

void GraphLayoutEngine::RunLayout(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        ComputeForces();
        UpdatePositions();
    }
    ApplyPositions();
}

shared_ptr<GraphNode> GraphLayoutEngine::FindNode(shared_ptr<CElement> el) {
    for (auto& node : nodes)
        if (node->element == el)
            return node;
    return nullptr;
}

void GraphLayoutEngine::ComputeForces() {
    // Répulsion
    for (auto& a : nodes) {
        for (auto& b : nodes) {
            if (a == b) continue;
            float dx = a->position.X - b->position.X;
            float dy = a->position.Y - b->position.Y;
            float distSq = dx * dx + dy * dy + 0.01f;
            float force = repulsionStrength / distSq;
            a->ApplyForce({ dx * force, dy * force });
        }
    }

    // Attraction
    for (auto& edge : edges) {
        float dx = edge.to->position.X - edge.from->position.X;
        float dy = edge.to->position.Y - edge.from->position.Y;
        float dist = std::fmax(sqrt(dx * dx + dy * dy), minDistance);
        float force = (dist - minDistance) * attractionStrength;
        PointF attraction = { dx * force, dy * force };
        edge.from->ApplyForce(attraction);
        edge.to->ApplyForce({ -attraction.X, -attraction.Y });
    }
}

void GraphLayoutEngine::UpdatePositions() {
    for (auto& node : nodes)
        node->UpdatePosition();
}

void GraphLayoutEngine::ApplyPositions() {
    for (auto& node : nodes) {
        node->element->m_point.x = static_cast<int>(node->position.X);
        node->element->m_point.y = static_cast<int>(node->position.Y);
    }
}
