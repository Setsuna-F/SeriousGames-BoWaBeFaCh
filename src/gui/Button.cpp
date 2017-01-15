#include "Button.hpp"
#include "Utility.hpp"
#include "SoundPlayer.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace GUI
{

Button::Button(State::Context context)
: mCallback()
, mSprite(context.textures->get(Textures::Buttons))
, mText("", context.fonts->get(Fonts::Main), 16)
, mIsToggle(false)
, mSounds(*context.sounds)
, mContext(context)
, mSoundPlayed(SoundEffect::Button)
{
	changeTexture(Normal);

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);

	srand(time(NULL));
	mSoundPlayed = static_cast<SoundEffect::ID>(rand() % 9 + SoundEffect::Pencil1);
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void Button::setToggle(bool flag)
{
	mIsToggle = flag;
}

bool Button::isSelectable() const
{
    return true;
}

void Button::select()
{
	Component::select();

	changeTexture(Selected);
}

void Button::deselect()
{
	Component::deselect();

	changeTexture(Normal);
}

void Button::activate()
{
	Component::activate();

	if(mSoundPlayed != SoundEffect::NoSound)
		mSounds.play(mSoundPlayed);

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (mIsToggle)
		changeTexture(Pressed);

	if (mCallback)
		mCallback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!mIsToggle)
		deactivate();
}

void Button::deactivate()
{
	Component::deactivate();

	if (mIsToggle)
	{
        // Reset texture to right one depending on if we are selected or not.
		if (isSelected())
			changeTexture(Selected);
		else
			changeTexture(Normal);
	}
	else
		changeTexture(Selected);
}

void Button::handleEvent(const sf::Event& event)
{
	sf::IntRect r(getPosition().x, getPosition().y, mSprite.getTextureRect().width*mSprite.getScale().x, mSprite.getTextureRect().height*mSprite.getScale().y);
	if (event.type == sf::Event::MouseMoved && r.contains(event.mouseMove.x, event.mouseMove.y) && !isSelected())
	{
		select();
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && r.contains(event.mouseButton.x, event.mouseButton.y))
	{
		changeTexture(Pressed);
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		changeTexture(Selected);
		if (r.contains(event.mouseButton.x, event.mouseButton.y))
			activate();
	}
	else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space))
	{
		changeTexture(Pressed);
	}
}

void Button::setSound(SoundEffect::ID s)
{
	mSoundPlayed = s;
}

void Button::setTexture(Textures::ID t)
{
	mSprite.setTexture(mContext.textures->get(t), true);
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void Button::changeTexture(Type buttonType)
{
	sf::IntRect textureRect(0, 50*buttonType, 200, 50);
	mSprite.setTextureRect(textureRect);
}

void Button::scale(float scaleX, float scaleY)
{
	mSprite.scale(scaleX, scaleY);
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(mSprite.getScale().x * bounds.width / 2.f, mSprite.getScale().y * bounds.height / 2.f);
}

}
