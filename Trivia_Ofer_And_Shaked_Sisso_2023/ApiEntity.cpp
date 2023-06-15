#include "ApiEntity.h"

void ApiEntity::checkForHtmlEntity(std::string& str)
{
	replaceHtmlEntity(str, "&lt;", "<");
	replaceHtmlEntity(str, "&gt;", ">");
	replaceHtmlEntity(str, "&amp;", "&");
	replaceHtmlEntity(str, "&quot;", "\"");
	replaceHtmlEntity(str, "&#039;", "\'");
	replaceHtmlEntity(str, "&shy;", "-");
	replaceHtmlEntity(str, "&eacute;", "e");
}

void ApiEntity::replaceHtmlEntity(std::string& str, const std::string& entity, const std::string& replacement)
{
	size_t pos = str.find(entity);
	while (pos != std::string::npos) {
		str.replace(pos, entity.length(), replacement);
		pos = str.find(entity, pos + replacement.length());
	}
}
