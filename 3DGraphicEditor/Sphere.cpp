#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, double radius, int meridians, int parallels, wxColour color) : Sphere(Position(x, y, z), radius, meridians, parallels, color) {}
Sphere::Sphere(Position center, double radius, int meridians, int parallels, wxColour color) :Drawable(color), _center(center), _radius(radius), _meridians(meridians), _parallels(parallels) {}

void Sphere::move(double x_shift, double y_shift, double z_shift) {
    _center.x += x_shift;
    _center.y += y_shift;
    _center.z += z_shift;
}

void Sphere::rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
    // Move center to origin
    move(-x_cord, -y_cord, -z_cord);

    std::vector<std::vector<double>> rotationMatrix = generate_rotation_matrix(alpha, beta, gamma);

    double x = _center.x * rotationMatrix[0][0] + _center.y * rotationMatrix[0][1] + _center.z * rotationMatrix[0][2];
    double y = _center.x * rotationMatrix[1][0] + _center.y * rotationMatrix[1][1] + _center.z * rotationMatrix[1][2];
    double z = _center.x * rotationMatrix[2][0] + _center.y * rotationMatrix[2][1] + _center.z * rotationMatrix[2][2];

    _center.x = x;
    _center.y = y;
    _center.z = z;

    // Move center back to original position
    move(x_cord, y_cord, z_cord);
}

void Sphere::draw_front(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            double x1 = _center.x + _radius * sin(phi) * cos(lambda);
            double y1 = _center.y + _radius * sin(phi) * sin(lambda);
            double x2 = _center.x + _radius * sin(phi) * cos(next_lambda);
            double y2 = _center.y + _radius * sin(phi) * sin(next_lambda);
            double x3 = _center.x + _radius * sin(next_phi) * cos(next_lambda);
            double y3 = _center.y + _radius * sin(next_phi) * sin(next_lambda);
            double x4 = _center.x + _radius * sin(next_phi) * cos(lambda);
            double y4 = _center.y + _radius * sin(next_phi) * sin(lambda);

            // Draw quad
            dc.DrawLine(x1, panelHeight - y1, x2, panelHeight - y2);
            dc.DrawLine(x2, panelHeight - y2, x3, panelHeight - y3);
            dc.DrawLine(x3, panelHeight - y3, x4, panelHeight - y4);
            dc.DrawLine(x4, panelHeight - y4, x1, panelHeight - y1);
        }
    }
}

void Sphere::draw_top(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            double x1 = _center.x + _radius * sin(phi) * cos(lambda);
            double z1 = _center.z + _radius * cos(phi);
            double x2 = _center.x + _radius * sin(phi) * cos(next_lambda);
            double z2 = _center.z + _radius * cos(phi);
            double x3 = _center.x + _radius * sin(next_phi) * cos(next_lambda);
            double z3 = _center.z + _radius * cos(next_phi);
            double x4 = _center.x + _radius * sin(next_phi) * cos(lambda);
            double z4 = _center.z + _radius * cos(next_phi);

            // Draw quad
            dc.DrawLine(x1, panelHeight - z1, x2, panelHeight - z2);
            dc.DrawLine(x2, panelHeight - z2, x3, panelHeight - z3);
            dc.DrawLine(x3, panelHeight - z3, x4, panelHeight - z4);
            dc.DrawLine(x4, panelHeight - z4, x1, panelHeight - z1);
        }
    }
}

void Sphere::draw_side(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    // Iterate over parallels
    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            double y1 = _center.y + _radius * sin(phi) * cos(lambda);
            double z1 = _center.z + _radius * cos(phi);
            double y2 = _center.y + _radius * sin(phi) * cos(next_lambda);
            double z2 = _center.z + _radius * cos(phi);
            double y3 = _center.y + _radius * sin(next_phi) * cos(next_lambda);
            double z3 = _center.z + _radius * cos(next_phi);
            double y4 = _center.y + _radius * sin(next_phi) * cos(lambda);
            double z4 = _center.z + _radius * cos(next_phi);

            dc.DrawLine(z1, panelHeight - y1, z2, panelHeight - y2);
            dc.DrawLine(z2, panelHeight - y2, z3, panelHeight - y3);
            dc.DrawLine(z3, panelHeight - y3, z4, panelHeight - y4);
            dc.DrawLine(z4, panelHeight - y4, z1, panelHeight - y1);
        }
    }
}

void Sphere::draw_perspective(wxDC& dc) {
    dc.SetPen(wxPen(_color));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    // Iterate over parallels
    const double phi_step = M_PI / _parallels;
    const double lambda_step = 2 * M_PI / _meridians;

    for (int i = 0; i < _parallels; ++i) {
        double phi = i * phi_step;
        double next_phi = (i + 1) * phi_step;

        // Iterate over meridians
        for (int j = 0; j < _meridians; ++j) {
            double lambda = j * lambda_step;
            double next_lambda = (j + 1) * lambda_step;

            // Compute vertices
            wxPoint p1_2d = Camera::project(Position(_center.x + _radius * sin(phi) * cos(lambda), _center.y + _radius * sin(phi) * sin(lambda), _center.z + _radius * cos(phi)));
            wxPoint p2_2d = Camera::project(Position(_center.x + _radius * sin(phi) * cos(next_lambda), _center.y + _radius * sin(phi) * sin(next_lambda), _center.z + _radius * cos(phi)));
            wxPoint p3_2d = Camera::project(Position(_center.x + _radius * sin(next_phi) * cos(next_lambda), _center.y + _radius * sin(next_phi) * sin(next_lambda), _center.z + _radius * cos(next_phi)));
            wxPoint p4_2d = Camera::project(Position(_center.x + _radius * sin(next_phi) * cos(lambda), _center.y + _radius * sin(next_phi) * sin(lambda), _center.z + _radius * cos(next_phi)));

            // Draw quad
            dc.DrawLine(p1_2d.x, p1_2d.y, p2_2d.x, p2_2d.y);
            dc.DrawLine(p2_2d.x, p2_2d.y, p3_2d.x, p3_2d.y);
            dc.DrawLine(p3_2d.x, p3_2d.y, p4_2d.x, p4_2d.y);
            dc.DrawLine(p4_2d.x, p4_2d.y, p1_2d.x, p1_2d.y);
        }
    }
}

void Sphere::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) {
    draw_front(dc1);
    draw_top(dc2);
    draw_side(dc3);
    draw_perspective(dc4);
}

std::string Sphere::save() const
{
    std::string result = "Sphere "
        + std::to_string(_center.x) + " " + std::to_string(_center.y) + " " + std::to_string(_center.z) + " "
        + std::to_string(_radius) + " " + std::to_string(_meridians) + " " + std::to_string(_parallels) + " "
        + std::to_string(_color.GetRGB()) + "\n";
    return result;
}
