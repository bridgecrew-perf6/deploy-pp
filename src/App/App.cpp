#include "App.hpp"

App::App(std::string name, std::string repository, std::string local,std::string branch,std::string webhookSecret,bool force, std::vector<Step> steps) : m_name(name), m_repository(repository), m_local(local),m_branch(branch),m_webhookSecret(webhookSecret),m_force(force), m_steps(steps)
{
}
std::string App::GetName() 
{
	return this->m_name;
}
std::string App::GetRemoteRepository()
{
	return this->m_repository;
}
std::string App::GetLocalRepositoryPath()
{
	return this->m_local;
}
std::vector<Step> App::GetSteps()
{
	return this->m_steps;
}
std::string App::GetWebhookSecret()
{
	return this->m_webhookSecret;
}
void App::Pull()
{
	std::string cmd = "git pull origin ";
	cmd += this->m_branch;

	if (this->m_force) cmd += " --force";

	try
	{
		int result = system(cmd.c_str());

		if (result != 0)
		{
			// TODO: Log error
		}
	}
	catch (const std::exception& ex)
	{
		// TODO: handle
	}
}
void App::TriggerActions()
{
	char cdArr[255];
	auto currentDirectory = _getcwd(cdArr, sizeof(cdArr));
	
	this->Pull();

	try
	{
		// Default: CD to directory
		auto cd = _chdir(this->GetLocalRepositoryPath().c_str());
		if (cd != 0)
		{
			// TODO: log error
			return;
		}
		//_wchdir();
		
		for (auto& action : this->m_steps)
		{
			// TODO: Log execution (if enabled)
			int result = system(action.GetCommand().c_str());
			if (result != 0)
			{
				// TODO: log failed post command
			}
		}

		//
	}
	catch (const std::exception& ex)
	{
		// TODO: handle
	}

	// TODO: Change back to default dir
	int result = _chdir(currentDirectory);

	if (result != 0)
	{
		// TODO: log error
	}
}