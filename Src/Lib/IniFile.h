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

#pragma once

namespace SCSScript
{
	class IniFile
	{
	public:
		struct Record 
		{
			String	Comments;
			Char	Commented;
			String	Section;
			String	Key;
			String	Value;
		};

		enum CommentChar 
		{
			Pound		='#',
			SemiColon	=';'
		};

	private:
		static Vector<Record>	GetSections(const String& FileName);
		static bool				Load(const String& FileName,Vector<Record>& content);	
		static bool				Save(const String& FileName,Vector<Record>& content);

		struct RecordSectionIs : std::unary_function<Record,bool> 
		{
			String section_;
			RecordSectionIs(const String& section) : section_(section) {}
			bool operator()(const Record& rec) const 
			{ 
				return rec.Section==section_; 
			}
		};

		struct RecordSectionKeyIs : std::unary_function<Record,bool> 
		{
			String section_;
			String key_;
			RecordSectionKeyIs(const String& section,const String& key) : section_(section),key_(key) {}
			bool operator()(const Record& rec) const 
			{ 
				return ((rec.Section==section_)&&(rec.Key==key_)); 
			}
		};

		struct AscendingSectionSort 
		{
			bool operator()(Record& Start,Record& End) 
			{
				return Start.Section<End.Section;
			}
		};

		struct DescendingSectionSort 
		{
			bool operator()(Record& Start,Record& End) 
			{
				return Start.Section>End.Section;
			}
		};

		struct AscendingRecordSort 
		{
			bool operator()(Record& Start,Record& End) 
			{
				return Start.Key<End.Key;
			}
		};

		struct DescendingRecordSort 
		{
			bool operator()(Record& Start,Record& End) 
			{
				return Start.Key>End.Key;
			}
		};

	public:
		IniFile();
		virtual ~IniFile();

		static bool				AddSection(const String& SectionName,const String& FileName);
		static bool				CommentRecord(CommentChar cc,const String& KeyName,const String& SectionName,const String& FileName);
		static bool				CommentSection(Char CommentChar,const String& SectionName,const String& FileName);
		static String			Content(const String& FileName);
		static bool				Create(const String& FileName);
		static bool				DeleteRecord(const String& KeyName,const String& SectionName,const String& FileName);
		static bool				DeleteSection(const String& SectionName,const String& FileName);
		static Vector<Record>	GetRecord(const String& KeyName,const String& SectionName,const String& FileName);
		static Vector<Record>	GetSection(const String& SectionName,const String& FileName);
		static Vector<String>	GetSectionNames(const String& FileName);
		static String			GetValue(const String& KeyName,const String& SectionName,const String& FileName);
		static bool				RecordExists(const String& KeyName,const String& SectionName,const String& FileName);
		static bool				RenameSection(const String& OldSectionName,const String& NewSectionName,const String& FileName);
		static bool				SectionExists(const String& SectionName,const String& FileName);
		static bool				SetRecordComments(String& Comments,const String& KeyName,const String& SectionName,const String& FileName);
		static bool				SetSectionComments(String& Comments,const String& SectionName,const String& FileName);
		static bool				SetValue(const String& KeyName,const String& Value,const String& SectionName,const String& FileName);
		static bool				Sorting(const String& FileName,bool Descending);
		static bool				UnCommentRecord(const String& KeyName,const String& SectionName,const String& FileName);
		static bool				UnCommentSection(const String& SectionName,const String& FileName);
	};
}

