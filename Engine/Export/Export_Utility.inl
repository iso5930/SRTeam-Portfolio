
CManagement* GetManagement(void)
{
	return ENGINE::CManagement::GetInstance();
}

CInfoSubject* GetInfoSubject(void)
{
	return ENGINE::CInfoSubject::GetInstance();
}

CEventManager* GetEventManager(void)
{
	return ENGINE::CEventManager::GetInstance();
}
