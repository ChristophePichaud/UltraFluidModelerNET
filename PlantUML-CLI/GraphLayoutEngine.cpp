#include "pch.h"
#include "GraphLayoutEngine.h"

GraphNode::GraphNode(shared_ptr<CElement> el, PointF pos)
    : element(el), position(pos), velocity({ 0, 0 }), accumulatedForce({ 0, 0 }) {
}

void GraphNode::ApplyForce(const PointF& force) {
    accumulatedForce.x += force.x;
    accumulatedForce.y += force.y;
}

void GraphNode::UpdatePosition(float damping) {
    velocity.x = accumulatedForce.x * damping;
    velocity.y = accumulatedForce.y * damping;
    position.x += velocity.x;
    position.y += velocity.y;
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
            float dx = a->position.x - b->position.x;
            float dy = a->position.y - b->position.y;
            float distSq = dx * dx + dy * dy + 0.01f;
            float force = repulsionStrength / distSq;
            a->ApplyForce({ dx * force, dy * force });
        }
    }

    // Attraction
    for (auto& edge : edges) {
        float dx = edge.to->position.x - edge.from->position.x;
        float dy = edge.to->position.y - edge.from->position.y;
        float dist = std::max(sqrt(dx * dx + dy * dy), minDistance);
        float force = (dist - minDistance) * attractionStrength;
        PointF attraction = { dx * force, dy * force };
        edge.from->ApplyForce(attraction);
        edge.to->ApplyForce({ -attraction.x, -attraction.y });
    }
}

void GraphLayoutEngine::UpdatePositions() {
    for (auto& node : nodes)
        node->UpdatePosition();
}

void GraphLayoutEngine::ApplyPositions() {
    for (auto& node : nodes) {
        node->element->m_point.x = static_cast<int>(node->position.x);
        node->element->m_point.y = static_cast<int>(node->position.y);
    }
}
