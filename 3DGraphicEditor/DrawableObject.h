#pragma once
#include "Drawable.h"

class DrawableObject : public Drawable
{
public:
	DrawableObject(wxColour color = Drawable::penColor, const std::string& type = "DrawableObject");

	void setColor(const wxColour& newColor);
	wxColour getColor() const
	{
		return _color;
	}

	void setLineWidth(int newLineWidth)
	{
		_lineWidth = newLineWidth;
	}
	int getLineWidth() const
	{
		return _lineWidth;
	}

	/// @brief Rysowanie figury
	/// @param dcFront - panel z widokiem z przodu
	/// @param dcTop - panel z widokiem z gory
	/// @param dcSide - panel z widokiem z boku
	/// @param dcPerspective - panel z widokiem z perspektywa
	virtual void draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) const;

	virtual void move(double xShift, double yShift, double zShift);

	virtual void rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma);

	virtual void render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const = 0;

	virtual std::string getInfo() const;

	virtual std::string save() const;

	int getGroupId() const { return _group_id; }
	void setGroupId(int newGroupId)
	{
		_group_id = newGroupId;
	}
	void highlightObject();

protected:
	int _group_id = 0;
	std::string _type;
	wxColour _color; /// @brief kolor obiektu
	int _lineWidth = Drawable::penWidth;
	std::vector<Position> _vertices;

	virtual void computeVertices() = 0;

private:
	wxTimer* _highlightTimer = nullptr; /// Timer for resetting the highlight
	const wxColour generateHighlight() const;
	void ResetHighlight(wxTimerEvent& event, wxColour prev);
};
