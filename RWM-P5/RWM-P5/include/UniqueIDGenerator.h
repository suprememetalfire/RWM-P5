#ifndef UNIQUEIDGENERATOR_H
#define UNIQUEIDGENERATOR_H

namespace GameUtilities
{
	/*!
	 * A singleton class that generates a unique ID for all in-game objects.
	 *
	 * The UniqueIDGenerator class maintains a current ID number, which is 
	 * incremented after each object ID assignment. This ID will always be 
	 * unique so that each game object can be referenced individually.
	 */
	class UniqueIDGenerator
	{
	private:
		static bool m_initialised;						//!< Whether the singleton has been initialised or not.
		static UniqueIDGenerator * m_instance;			//!< A pointer to the singleton instance.
		static long m_currentID;						//!< Current unique ID.

		//! Constructor.
		UniqueIDGenerator() {}
	public:
		/*! 
		 *	Returns the instance of the singleton, and initialises
		 *	it if it hasn't been already.
		 *
		 *	@return Instance of the singleton.
		 */
		static UniqueIDGenerator * getInstance();

		//! Destructor.
		~UniqueIDGenerator();

		/*! 
		 *	Returns a new unique ID for game entity creation and 
		 *	increments m_currentID.
		 *
		 *	@return New unique ID.
		 */
		long getNewID();

	}; // class UniqueIDGenerator
} // namespace GameUtilities
#endif