#pragma once
#include <string>
enum class ParaErrorType
{
	COMPONENT_ALREADY_PRESENT = 101,
	OBJECT_NAME_ALREADY_PRESENT
};
class ParaEngineError
{
public:
	ParaEngineError(ParaErrorType type, const std::string & errorMsg)
	{
		this->errorMsg = errorMsg;
		this->errorType = type;
	}
	std::string getErrorMsg() { return errorMsg; }
	ParaErrorType getErrorType() { return errorType; }
	~ParaEngineError() {}
private:
	std::string errorMsg;
	ParaErrorType errorType;
};