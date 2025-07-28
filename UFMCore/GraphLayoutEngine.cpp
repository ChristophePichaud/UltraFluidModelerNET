#include "pch.h"
#include "UFMCore\GraphLayoutEngine.h"

/*
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
    {
        node->UpdatePosition();
    }
}

void GraphLayoutEngine::ApplyPositions() 
{
	int elementsCount = 0;
    for (auto& node : nodes) 
    {
		elementsCount++;

        node->element->m_point.x = static_cast<int>(node->position.X);
        node->element->m_point.y = static_cast<int>(node->position.Y);

        node->element->m_rect.top = node->element->m_point.y;
        node->element->m_rect.left = node->element->m_point.x;
        node->element->m_rect.right = node->element->m_point.x + 100 + 50;
        node->element->m_rect.bottom = node->element->m_point.y + (30 * elementsCount);

        // dump
		wprintf(L"Element %s at (%d, %d)\n", node->element->m_name.c_str(), node->element->m_point.x, node->element->m_point.y);
    }
}
*/

GraphLayoutEngine::GraphLayoutEngine(int width, int height)
    : maxWidth(width), maxHeight(height) {
}

void GraphLayoutEngine::AddElement(shared_ptr<CElement> el) {
    float margin = 50.0f;
    PointF initial = {
        margin + static_cast<float>(rand() % (maxWidth - static_cast<int>(margin * 2))),
        margin + static_cast<float>(rand() % (maxHeight - static_cast<int>(margin * 2)))
    };
    nodes.push_back(make_shared<GraphNode>(el, initial));
}

void GraphLayoutEngine::AddConnector(shared_ptr<CElement> from, shared_ptr<CElement> to) {
    auto nodeFrom = FindNode(from);
    auto nodeTo = FindNode(to);
    if (nodeFrom && nodeTo)
        edges.push_back({ nodeFrom, nodeTo });
}

shared_ptr<GraphNode> GraphLayoutEngine::FindNode(shared_ptr<CElement> el) {
    for (auto& node : nodes)
        if (node->element == el) return node;
    return nullptr;
}

void GraphLayoutEngine::RunLayout(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        ComputeForces();
        UpdatePositions();
    }
    ApplyPositions();
}

void GraphLayoutEngine::ComputeForces() {
    for (auto& node : nodes)
        node->velocity = { 0.0f, 0.0f };

    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = i + 1; j < nodes.size(); ++j) {
            auto& a = nodes[i];
            auto& b = nodes[j];

            float dx = b->position.X - a->position.X;
            float dy = b->position.Y - a->position.Y;
            float distSq = dx * dx + dy * dy + 0.1f;

            float force = repulsionStrength / distSq;
            float fx = force * dx;
            float fy = force * dy;

            a->velocity.X -= fx;
            a->velocity.Y -= fy;
            b->velocity.X += fx;
            b->velocity.Y += fy;
        }
    }

    for (auto& edge : edges) {
        float dx = edge.to->position.X - edge.from->position.X;
        float dy = edge.to->position.Y - edge.from->position.Y;
        float dist = sqrt(dx * dx + dy * dy) + 0.1f;

        float force = attractionStrength * (dist - minDistance);
        float fx = force * dx / dist;
        float fy = force * dy / dist;

        edge.from->velocity.X += fx;
        edge.from->velocity.Y += fy;
        edge.to->velocity.X -= fx;
        edge.to->velocity.Y -= fy;
    }
}

void GraphLayoutEngine::UpdatePositions() {
    for (auto& node : nodes) {
        node->position.X += node->velocity.X * 0.1f;
        node->position.Y += node->velocity.Y * 0.1f;
    }
}

PointF GraphLayoutEngine::ClampPosition(const PointF& pos) {
    PointF clamped;
    clamped.X = fmax(0.0f, fmin(pos.X, static_cast<float>(maxWidth)));
    clamped.Y = fmax(0.0f, fmin(pos.Y, static_cast<float>(maxHeight)));
    return clamped;
}

void GraphLayoutEngine::ApplyPositions() 
{
    //for (auto& node : nodes) 
    //{
    //    PointF pos = ClampPosition(node->position);
    //    node->element->m_point.x = static_cast<int>(pos.X);
    //    node->element->m_point.y = static_cast<int>(pos.Y);
    //}

    int elementsCount = 0;
    for (auto node : nodes)
    {
        elementsCount++;

        PointF pos = ClampPosition(node->position);
        node->element->m_point.x = static_cast<int>(pos.X);
        node->element->m_point.y = static_cast<int>(pos.Y);

        node->element->m_rect.top = node->element->m_point.y;
        node->element->m_rect.left = node->element->m_point.x;
        node->element->m_rect.right = node->element->m_point.x + 100 + 50;
        node->element->m_rect.bottom = node->element->m_point.y + (30 * node->element->m_ElementsCounts);

        // dump
        wprintf(L"Element %s at (%d, %d)\n", node->element->m_name.c_str(), node->element->m_point.x, node->element->m_point.y);
    }

}
