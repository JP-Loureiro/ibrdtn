#ifndef IBRCOMMON_CONDITIONAL_H_
#define IBRCOMMON_CONDITIONAL_H_

#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include "ibrcommon/thread/Mutex.h"
#include "ibrcommon/Exceptions.h"

namespace ibrcommon
{
	class Conditional : public Mutex
	{
		public:
			class ConditionalAbortException : public ibrcommon::Exception
			{
			public:
				enum abort_t
				{
					COND_TIMEOUT = 0,
					COND_ABORT = 1,
					COND_ERROR = 2
				};

				ConditionalAbortException(abort_t abort, string what = "Conditional has been unblocked.") throw() : ibrcommon::Exception(what), reason(abort)
				{
				};

				const abort_t reason;
			};

			Conditional();
			virtual ~Conditional();

			void signal(bool broadcast = false);

			/*
			 * Wait until signal() is called or the timeout exceeds.
			 * @param timeout A timeout in milliseconds.
			 * @throw ConditionalAbortException If a timeout occur or the Conditional is aborted by abort() the ConditionalAbortException is thrown.
			 */
			void wait(size_t timeout = 0) throw (ConditionalAbortException);
			void wait(struct timespec *ts) throw (ConditionalAbortException);

			/**
			 * Abort all waits on this conditional.
			 */
			void abort();

			/**
			 * Removes the abort call off this conditional.
			 */
			void reset();

			/**
			 * Convert a millisecond timeout into use for high resolution
			 * conditional timers.
			 * @param timeout to convert.
			 * @param hires timespec representation to fill.
			 */
			static void gettimeout(size_t timeout, struct timespec *hires);

		private:
			bool isLocked();

			class attribute
			{
			public:
				pthread_condattr_t attr;
				attribute();
			};

			pthread_cond_t cond;

			static attribute attr;

			bool _abort;
	};

	template<class T, T block>
	class StatefulConditional : public Conditional
	{
	public:
		StatefulConditional(T state) : _state(state) {};
		virtual ~StatefulConditional() {};

		void setState(T state)
		{
			if (ifState(block)) return;
			_state = state;
			this->signal(true);
		}

		bool waitState(T state)
		{
			while (!ifState(state))
			{
				if (ifState(block)) return false;
				wait();
			}

			return true;
		}

		T getState()
		{
			return _state;
		}

		bool ifState(T state)
		{
			return (state == _state);
		}

	private:
		T _state;
	};
}

#endif /*CONDITIONAL_H_*/
