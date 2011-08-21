#ifndef PAUSABLECLOCK_HPP
#define PAUSABLECLOCK_HPP
 
/*!
 \file pausable_clock.hpp
 \brief Definition and implémentation of PausableClock class.
 */
 
#include <SFML/System.hpp>
 
/*!
 \class PausableClock
 \brief sf::Clock with Pause function.
 */
class PausableClock : public sf::Clock
{
	public :
		/*!
		\brief Semi-default ctor.
		\param pause : does the clock start paused ?
		 */
		PausableClock(bool paused = false)
	: am_i_paused(false)
				, my_time(0.f)
				{
					//
				}
 
		/*!
				\brief Set the clock in 'pause' mode.
		 */
				void Pause(void)
				{
			// If not yet paused...
					if (!am_i_paused)
					{
						am_i_paused = true;
						my_time += sf::Clock::GetElapsedTime();
					}
				}
 
		/*!
				\brief Start the clock (again).
		 */
				void Play(void)
				{
			// If not yet started...
					if (am_i_paused)
					{
						sf::Clock::Reset();
						am_i_paused = false;
					}
				}
 
		/*!
				\brief Get the time elapsed since last Reset.
		 */
				float GetElapsedTime(void) const
				{
			// If not paused...
					if (!am_i_paused)
						return my_time + sf::Clock::GetElapsedTime();
					else
						return my_time;
				}
 
		/*!
				\brief Reset the clock.
				\param pause : does the clock start paused ?
		 */
				void Reset(bool paused = false)
				{
					am_i_paused = paused;
					my_time = 0.f;
					sf::Clock::Reset();
				}
				
				bool Toggle()
				{
					if(am_i_paused)
					{
						Play();
						return true;
					}
					Pause();
					return false;
				}
				void Stop()
				{
					Reset();
					am_i_paused=true;
					my_time=0;
				}

 
	private :
		/*!
		\brief Is the PausableClock paused ?
		 */
		bool am_i_paused;
 
		/*!
		\breif Time buffer.
		 */
		float my_time;
};
 
#endif // PAUSABLECLOCK_HPP
