#include "stage.h"

#include <cassert>
#include <map>

Stage::Stage()
    : center_ (0.5f, 0.5f)
    , size_(1.0f, 1.0f)
{

}

//!\brief Sets the view from the specififed view
void Stage::set_view(sf::View view)
{
    view_ = view;
}

//!\brief Sets the camera params
void Stage::set_view(sf::FloatRect rect)
{
    view_.reset(rect);
}

//!\brief Sets the viewport in the window
void Stage::set_viewport(sf::FloatRect rect)
{
    view_.setViewport(rect);
}

void Stage::zoom(float zoom)
{
    view_.zoom(zoom);
}

void Stage::set_center(sf::Vector2f center)
{
    view_.setCenter(center);
}

void Stage::set_size(sf::Vector2f size)
{
    view_.setSize(size.x, size.y);
}

void Stage::move(sf::Vector2f distance)
{
    view_.move(distance);
}

void Stage::add(DrawablePtr drawable)
{
    drawables_.push_back(drawable);
}

void Stage::remove(DrawablePtr drawable)
{
    for(size_t i=0; i<drawables_.size(); ++i)
    {
        if(drawables_[i] == drawable)
        {
            drawables_.erase(drawables_.begin() + i);
            break;
        }
    }
}

void Stage::draw(std::shared_ptr<sf::RenderWindow> window)
{
    assert(window);

    std::map<uint32_t, std::vector<DrawablePtr>> bins;
    
    // Create render bins and sort the drawables into the bins
    for(size_t i=0; i<drawables_.size(); ++i)
    {
        uint32_t bin_id = drawables_[i]->get_layer();
        if(bins.count(bin_id) == 0)
        {
            bins.insert(std::make_pair(bin_id, std::vector<DrawablePtr>()));
        }

        bins[bin_id].push_back(drawables_[i]);
    }
    
    // Configure the window with our view
    window->setView(view_);
    
    // Draw each render bin
    for(auto& bin : bins)
    {
        for(auto& drawable : bin.second)
        {
            drawable->draw(window);
        }
    }
    
    // Reset the window to the default
    window->setView(window->getDefaultView());
}
