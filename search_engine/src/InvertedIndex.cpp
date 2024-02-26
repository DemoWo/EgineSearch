#include "InvertedIndex.h"

std::mutex mutexIndexMap;

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs)
{
    if (input_docs.empty())
    {
        std::cerr << "\t- Indexing: no content in docs content base\n";
        return;
    }

    indexingIsOngoing = true;

    freq_dictionary.clear();
    size_t docId = 0;

    std::vector<std::thread> threads;
    for (const auto& content : input_docs)
    {
        threads.emplace_back(&InvertedIndex::indexTheFile, this, content, docId);
        ++docId;
    }
    indexingIsOngoing = false;

    for (auto &it : threads)
        it.join();
}

void InvertedIndex::indexTheFile(const std::string& fileContent, size_t docId){
    std::map<std::string, Entry> fileFreqDictionary;
    Entry entry{};
    entry.doc_id = docId;
    entry.count = 1;
    std::istringstream ist(fileContent);

    for (std::string word; ist >> word; ) {
        std::transform(word.begin(), word.end(), word.begin(),[](unsigned char c){ return std::tolower(c); });
        std::pair<std::string, Entry> file_word_frequency {word, entry};
        if (!fileFreqDictionary.emplace(file_word_frequency).second) {
            fileFreqDictionary.find(word)->second.count += 1;
        }
    }

    mutexIndexMap.lock();
    for (const auto& wordIterator : fileFreqDictionary) {
        std::pair<std::string, std::vector<Entry>> wordFrequency;
        wordFrequency.first = wordIterator.first;
        std::vector<Entry> entryVector {wordIterator.second};
        wordFrequency.second = entryVector;
        if (!freq_dictionary.emplace(wordFrequency).second)
        {
            freq_dictionary.find(wordFrequency.first)->second.push_back(wordIterator.second);
        }
    }
    mutexIndexMap.unlock();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    if (indexingIsOngoing)
    {
        std::cout << "Index is ongoing, please repeat the request later.\n";
        return {};
    }
    auto it = freq_dictionary.find(word);
    if (it != freq_dictionary.end()) {
        return it->second;
    } else {
        return {};
    }
}