#include "DrawableObject.h"

DrawableObject::DrawableObject(wxColour color, const std::string& type) : _color(color), _type(type) {};

void DrawableObject::highlightObject()
{
	if (!_highlightTimer)
	{
		wxColour colorBeforeHighlight = _color;

		_color = generateHighlight();

		_highlightTimer = new wxTimer();
		_highlightTimer->StartOnce(Drawable::highlight_duration_ms);

		// Bind the timer event
		_highlightTimer->Bind(wxEVT_TIMER, [this, colorBeforeHighlight](wxTimerEvent& event) {
			ResetHighlight(event, colorBeforeHighlight);
			});
	}
}

const wxColour DrawableObject::generateHighlight() const {
	return wxColour(
		std::min(_color.GetRed() - highlight_factor * 255, 255.0),
		std::min(_color.GetGreen() - highlight_factor * 255, 255.0),
		std::min(_color.GetBlue() - highlight_factor * 255, 255.0)
	);
};

void  DrawableObject::ResetHighlight(wxTimerEvent& event, wxColour prev)
{
	_color = prev;
	_highlightTimer->Stop(); // Stop the timer
	delete _highlightTimer; // Clean up the timer object
	_highlightTimer = nullptr;
}

void DrawableObject::draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) const
{
	render(dcFront, Camera::projectFront);
	render(dcTop, Camera::projectTop);
	render(dcSide, Camera::projectSide);
	render(dcPerspective, Camera::projectPerspective);
}

void DrawableObject::move(double xShift, double yShift, double zShift) {
	for (auto& vertex : _vertices)
	{
		vertex.shift(xShift, yShift, zShift);
	}
}

void DrawableObject::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) {
	for (auto& vertex : _vertices)
	{
		vertex.rotate(Position(xPivot, yPivot, zPivot), alpha, beta, gamma);
	}
}

std::string DrawableObject::save() const {
	std::string tmp;

	tmp += _type + " ";
	tmp += std::to_string(_group_id) + " ";
	tmp += std::to_string(_color.GetRGB()) += " ";
	tmp += std::to_string(_lineWidth) + " ";
	tmp += std::to_string(_vertices.size()) + " ";

	for (const auto& vertex : _vertices)
	{
		tmp += vertex.toString() + " ";
	}

	return tmp;
}

std::string DrawableObject::getInfo() const {
	return _type;
}

void DrawableObject::setColor(const wxColour& newColor) {
	_color = newColor;
}