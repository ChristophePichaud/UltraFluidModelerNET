#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include "Element.h" // Pour CElement
using namespace std;

class AFX_EXT_CLASS GraphNode {
public:
    shared_ptr<CElement> element;
    PointF position;
    PointF velocity;
    PointF accumulatedForce;

    GraphNode(shared_ptr<CElement> el, PointF pos);
    void ApplyForce(const PointF& force);
    void UpdatePosition(float damping = 0.85f);
};

class AFX_EXT_CLASS GraphEdge {
public:
    shared_ptr<GraphNode> from;
    shared_ptr<GraphNode> to;

    GraphEdge(shared_ptr<GraphNode> a, shared_ptr<GraphNode> b);
};

class AFX_EXT_CLASS GraphLayoutEngine {
public:
    void AddElement(shared_ptr<CElement> el);
    void AddConnector(shared_ptr<CElement> from, shared_ptr<CElement> to);
    void RunLayout(int iterations = 100);

private:
    vector<shared_ptr<GraphNode>> nodes;
    vector<GraphEdge> edges;

    const float repulsionStrength = 10000.0f;
    const float attractionStrength = 0.01f;
    const float minDistance = 50.0f;

    shared_ptr<GraphNode> FindNode(shared_ptr<CElement> el);
    void ComputeForces();
    void UpdatePositions();
    void ApplyPositions();
};
