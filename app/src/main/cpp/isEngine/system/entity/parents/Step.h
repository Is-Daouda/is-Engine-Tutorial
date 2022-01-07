/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef STEP_H_INCLUDED
#define STEP_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Provides methods to manage the step of an object mechanism
////////////////////////////////////////////////////////////
class Step
{
public:
    Step() :
        m_step(0)
    {}

    Step(int step) :
        m_step(step)
    {}

    virtual void setStep(int val)
    {
        m_step = val;
    }

    virtual void addStep()
    {
        m_step++;
    }

    virtual void reduceStep()
    {
        m_step--;
    }

    virtual int getStep() const
    {
        return m_step;
    }

protected:
    int m_step;
};
}
#endif // STEP_H_INCLUDED
