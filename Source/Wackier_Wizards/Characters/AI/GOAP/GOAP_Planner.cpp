// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP_Planner.h"
#include "GOAP_Belief.h"
#include "GOAP_Goal.h"
#include "GOAP_Action.h"
#include "GOAP_Node.h"
#include "GOAP_Agent.h"
#include "GOAP_Plan.h"

UGOAP_Planner::UGOAP_Planner()
{
}

UGOAP_Plan* UGOAP_Planner::Plan(UGOAP_Agent* agent, TArray<UGOAP_Goal*> goals, UGOAP_Goal* lastGoal)
{
	//Filters out goals that have been fulfilled.
	TArray<UGOAP_Goal*> orderedGoals = goals.FilterByPredicate([&](const UGOAP_Goal* index) { return !(const_cast<UGOAP_Goal*>(index)->CheckIfFulfilled()); });

	//Order goals based on their priority value. If a goal is the same as the last goal, reduce it's priority by one to minimise repetition.
	if (lastGoal == nullptr)
	{
		orderedGoals.Sort([](const UGOAP_Goal& A, const UGOAP_Goal& B) { return &A._priority < &B._priority; });
	}
	else
	{
		orderedGoals.Sort([lastGoal](const UGOAP_Goal& A, const UGOAP_Goal& B) { return (&A == const_cast<UGOAP_Goal*>(lastGoal)) ? &A._priority < &B._priority - 1 : &A._priority < &B._priority; });
	}

	for (UGOAP_Goal* goal : orderedGoals)
	{
		//Creates a GOAP_Node for the goal, and checks if a path of actions that achieve that goal exists.
		TObjectPtr<UGOAP_Node> goalNode = NewObject<UGOAP_Node>();
		goalNode->Init(nullptr, nullptr, goal->_desiredEffects, 0);

		//Recursive function that validates if a path to the goal is achievable. 
		if (FindPath(goalNode, agent->GetActions()) == true)
		{
			//If the goalNode has no neighbours (actions) or contains no action itself, the node is 'dead' and the goal is discarded.
			if (goalNode->IsDead() == true)
			{
				continue;
			}

			//If a path is successful, iterates through the potential action path and orders them by cost.
			TArray<UGOAP_Action*> actionStack;

			while (goalNode->neighbours.Num() > 0)
			{
				goalNode->neighbours.Sort([](const UGOAP_Node& a, const UGOAP_Node& b) { return a.cost < b.cost; });
				TObjectPtr<UGOAP_Node> cheapestNeighbour = goalNode->neighbours.Pop();

				goalNode = cheapestNeighbour;
				actionStack.Push(cheapestNeighbour->action.Get());
			}

			//Creates a plan using the found path, and then returns the plan.
			TObjectPtr<UGOAP_Plan> plan = NewObject<UGOAP_Plan>();
			plan->Init(goal, actionStack, goalNode->cost);

			return plan;
		}
	}

	return nullptr;
}

bool UGOAP_Planner::FindPath(UGOAP_Node* parent, TArray<UGOAP_Action*> actions)
{
	//Sorts the actions by cost and begins to iterate through them
	actions.Sort([](const UGOAP_Action& a, const UGOAP_Action& b) { return a._cost < b._cost; });

	for (UGOAP_Action* action : actions)
	{
		//Iterates through the parent requiredEffects (this is the goal when first called from the Plan() function), and discards the ones that are complete
		TArray<UGOAP_Belief*> requiredEffects = parent->requiredEffects;

		requiredEffects.RemoveAll([&](const UGOAP_Belief* index) { return const_cast<UGOAP_Belief*>(index)->Evaluate(); });

		//If all of the required effects are true, the goal can be achieved with the current actions, so return true.
		if (requiredEffects.Num() == 0)
		{
			return true;
		}

		//Checks to see if the action contains any effects that are needed to achieve the goal.
		if (action->_effects.Contains(*requiredEffects.CreateIterator()) == true)
		{
			//Removes any required effects (necessary to reach the goal) that the action fulfills.
			TArray<UGOAP_Belief*>* newRequiredEffects = new TArray<UGOAP_Belief*>(requiredEffects);
			newRequiredEffects->RemoveAll([&](const UGOAP_Belief* index) { return action->_effects.Contains(index); });

			//If the action has any preconditions (effects needed to start this action), add them to the requiredEffects.
			for (UGOAP_Belief* belief : action->_preconditions)
			{
				if (newRequiredEffects->Contains(belief) == false)
				{
					newRequiredEffects->Add(belief);
				}
			}

			//Remove the action from the available actions.
			TArray<UGOAP_Action*> newAvailableActions = TArray<UGOAP_Action*>(actions);
			newAvailableActions.Remove(action);

			//Create a new Node.
			TObjectPtr<UGOAP_Node> newNode = NewObject<UGOAP_Node>();
			newNode->Init(parent, action, *newRequiredEffects, parent->cost + action->_cost);

			//Checks if a path can be found using the new Node. If true, add it to the parent's neighbours and remove all of the actions preconditions from the required effects (as they can be fulfilled)
			if (FindPath(newNode, newAvailableActions) == true)
			{
				parent->neighbours.Add(newNode);
				newRequiredEffects->RemoveAll([&](const UGOAP_Belief* index) { return newNode->action->_preconditions.Contains(index); });
			}

			//If there are no more required effect, the path can achieve the goal.
			if (newRequiredEffects->Num() == 0)
			{
				return true;
			}
		}
	}

	//Return false if the goal can't be achieved with the available actions.
	return false;
}
