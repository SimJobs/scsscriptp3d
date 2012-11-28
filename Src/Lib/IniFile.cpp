/*
    This file is part of SCSScript.

    Copyright (C) 2006-2012 by Nick Sharmanzhinov

    SCSScript is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SCSScript is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SCSScript.  If not, see <http://www.gnu.org/licenses/>.

    Nick Sharmanzhinov
    except134@gmail.com
*/

#include "PCH.h"

namespace SCSScript
{
	IniFile::IniFile()
	{
	}

	IniFile::~IniFile()
	{
	}

	void Trim(String& str,const String& ChrsToTrim=" \t\n\r",int TrimDir=0)
	{
		size_t startIndex=str.find_first_not_of(ChrsToTrim);
		if(startIndex==String::npos) { 
			str.erase(); 
			return; 
		}
		if(TrimDir<2)
			str=str.substr(startIndex,str.size()-startIndex);
		if(TrimDir!=1)
			str=str.substr(0,str.find_last_not_of(ChrsToTrim)+1);
	}

	bool IniFile::Load(const String& FileName,Vector<Record>& content)
	{
		String s;																
		String CurrentSection;													

		IFileStream inFile(FileName.c_str());									
		if(!inFile.is_open())
			return false;														
		content.clear();														

		String comments="";														

		while(!std::getline(inFile,s).eof()) {
			Trim(s);															
			if(!s.empty()) {
				Record r;														

				if((s[0]=='#')||(s[0]==';')) {
					if((s.find('[')==String::npos)&&(s.find('=')==String::npos)) {
						comments+=s+'\n';										
					} else {
						r.Commented=s[0];										
						s.erase(s.begin());										
						Trim(s);
					}															
				} else 
					r.Commented=' ';											

				if(s.find('[')!=String::npos) {		
					s.erase(s.begin());											
					s.erase(s.find(']'));										
					r.Comments=comments;										
					comments="";												
					r.Section=s;												
					r.Key="";													
					r.Value="";													
					CurrentSection=s;
				}

				if(s.find('=')!=String::npos) {
					r.Comments=comments;										
					comments="";												
					r.Section=CurrentSection;									
					r.Key=s.substr(0,s.find('='));								
					r.Value=s.substr(s.find('=')+1);							
				}
				if(comments=="")												
					content.push_back(r);										
			}
		}

		inFile.close();															
		return true;
	}

	bool IniFile::Save(const String& FileName,Vector<Record>& content)
	{
		OFileStream outFile(FileName.c_str());								
		if(!outFile.is_open()) 
			return false;									

		for(int i=0;i<(int)content.size();i++) {
			outFile << content[i].Comments;										
			if(content[i].Key=="")												
				outFile << content[i].Commented << "[" << content[i].Section << "]" << std::endl;						
			else
				outFile << content[i].Commented << content[i].Key << "=" << content[i].Value << std::endl;						
		}

		outFile.close();														
		return true;
	}

	String IniFile::Content(const String& FileName)
	{
		String s="";															
		Vector<Record> content;

		if (Load(FileName,content)) {
			for(int i=0;i<(int)content.size();i++) 			{
				if(content[i].Comments != "") 
					s+=content[i].Comments;			
				if(content[i].Commented != ' ') 
					s+=content[i].Commented;		
				if((content[i].Key==""))										
					s+='['+content[i].Section+']';							
				else s+=content[i].Key+'='+content[i].Value;					

				if(i!=content.size()) 
					s+='\n';								
			}
			return s;															
		}

		return "";
	}

	Vector<String> IniFile::GetSectionNames(const String& FileName)
	{
		Vector<String> data;													
		Vector<Record> content;

		if(Load(FileName,content)) {
			for(int i=0;i<(int)content.size();i++) {
				if(content[i].Key =="")											
					data.push_back(content[i].Section);							
			}
		}

		return data;															
	}

	Vector<IniFile::Record> IniFile::GetSection(const String& SectionName,const String& FileName)
	{
		Vector<Record> data;								
		Vector<Record> content;													

		if(Load(FileName,content)) {
			for(int i=0;i<(int)content.size();i++) {
				if((content[i].Section==SectionName)&&(content[i].Key!=""))					
					data.push_back(content[i]);				
			}
		}

		return data;										
	}

	bool IniFile::RecordExists(const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));			
			if(iter==content.end()) 
				return false;							
		}
		return true;														
	}

	bool IniFile::SectionExists(const String& SectionName,const String& FileName)
	{
		Vector<Record> content;											

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionIs(SectionName));					
			if(iter==content.end()) 
				return false;						
		}
		return true;													
	}

	Vector<IniFile::Record> IniFile::GetRecord(const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> data;												
		Vector<Record> content;												

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));			
			if(iter==content.end()) 
				return data;							

			data.push_back (*iter);											
		}
		return data;														
	}

	String IniFile::GetValue(const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> content=GetRecord(KeyName,SectionName,FileName);		

		if(!content.empty())												
			return content[0].Value;										

		return "";															
	}

	bool IniFile::SetValue(const String& KeyName,const String& Value,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			if(!SectionExists(SectionName,FileName)) {
				Record s={"",' ',SectionName,"",""};						
				Record r={"",' ',SectionName,KeyName,Value};				
				content.push_back(s);										
				content.push_back(r);										
				return Save(FileName,content);								
			}

			if(!RecordExists(KeyName,SectionName,FileName)) {
				Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionIs(SectionName));					
				iter++;														
				Record r={"",' ',SectionName,KeyName,Value};				
				content.insert(iter,r);										
				return Save(FileName,content);								
			}

			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));			

			iter->Value=Value;												
			return Save(FileName,content);									
		}

		return false;														
	}

	bool IniFile::RenameSection(const String& OldSectionName,const String& NewSectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			for(Vector<Record>::iterator iter=content.begin();iter<content.end();iter++) {
				if(iter->Section==OldSectionName)							
					iter->Section=NewSectionName;							
			}
			return Save(FileName,content);									
		}

		return false;														
	}

	bool IniFile::CommentRecord(CommentChar cc,const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));			

			if(iter==content.end()) 
				return false;							

			iter->Commented=cc;										
			return Save(FileName,content);									

		}
		return false;														
	}

	bool IniFile::UnCommentRecord(const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));			

			if(iter==content.end()) 
				return false;							

			iter->Commented=' ';											
			return Save(FileName,content);									

		}
		return false;														
	}

	bool IniFile::CommentSection(char CommentChar,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			for(Vector<Record>::iterator iter=content.begin();iter<content.end();iter++) {
				if(iter->Section==SectionName)								
					iter->Commented=CommentChar;							
			}
			return Save(FileName,content);									
		}

		return false;														
	}

	bool IniFile::UnCommentSection(const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			for(Vector<Record>::iterator iter=content.begin();iter<content.end();iter++) {
				if(iter->Section==SectionName)								
					iter->Commented=' ';									
			}																
			return Save(FileName,content);									
		}

		return false;														
	}

	bool IniFile::DeleteRecord(const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));			

			if(iter==content.end()) 
				return false;							

			content.erase(iter);											
			return Save(FileName,content);									
		}

		return false;														
	}

	bool IniFile::DeleteSection(const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			for(int i=(int)content.size()-1;i>-1;i--) {							
				if(content[i].Section==SectionName)							
					content.erase(content.begin()+i);						
			}

			return Save(FileName,content);									
		}
		return false;														
	}

	bool IniFile::SetSectionComments(String& Comments,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			for(Vector<Record>::iterator iter=content.begin();iter<content.end();iter++) {
				if((iter->Section==SectionName)&&(iter->Key=="")) {	
					if(Comments.size()>=2) {
						if(Comments.substr(Comments.size()-2)!="\n")
							Comments+="\n";
					}
					iter->Comments=Comments;

					return Save(FileName,content);
				}
			}
		}
		return false;
	}

	bool IniFile::SetRecordComments(String& Comments,const String& KeyName,const String& SectionName,const String& FileName)
	{
		Vector<Record> content;

		if(Load(FileName,content)) {
			Vector<Record>::iterator iter=std::find_if(content.begin(),content.end(),IniFile::RecordSectionKeyIs(SectionName,KeyName));		

			if(iter==content.end()) 
				return false;						

			if(Comments.size()>=2) {
				if(Comments.substr(Comments.size()-2)!="\n")			
					Comments+="\n";										
			}
			iter->Comments=Comments;									
			return Save(FileName,content);								
		}

		return false;													
	}

	Vector<IniFile::Record> IniFile::GetSections(const String& FileName)
	{
		Vector<Record> data;												
		Vector<Record> content;														

		if(Load(FileName,content)) {
			for(int i=0;i<(int)content.size();i++) {
				if(content[i].Key=="")										
					data.push_back(content[i]);								
			}
		}

		return data;														
	}

	bool IniFile::Sorting(const String& FileName,bool Descending)
	{
		Vector<IniFile::Record> content;									
		Vector<IniFile::Record> sections=GetSections(FileName);				

		if(!sections.empty()) {
			if(Descending)													
				Sort(sections.begin(),sections.end(),DescendingSectionSort());
			else										
				Sort(sections.begin(),sections.end(),AscendingSectionSort());

			for(Vector<Record>::iterator iter=sections.begin();iter<sections.end();iter++) {																		
				content.push_back(*iter);

				Vector<IniFile::Record> records=GetSection(iter->Section,FileName);

				if(Descending)	
					Sort(records.begin(),records.end(),DescendingRecordSort());
				else			
					Sort(records.begin(),records.end(),AscendingRecordSort());

				for(Vector<Record>::iterator it=records.begin();it<records.end();it++)
					content.push_back(*it);	
			}

			return Save(FileName,content);	
		}

		return false;
	}

	bool IniFile::AddSection(const String& SectionName,const String& FileName)
	{
		Vector<Record> content;												

		if(Load(FileName,content)) {
			Record s={"",' ',SectionName,"",""};							
			content.push_back(s);											
			return Save(FileName,content);									
		}

		return false;														
	}

	bool IniFile::Create(const String& FileName)
	{
		Vector<Record> content;												
		return Save(FileName,content);										
	}

}

