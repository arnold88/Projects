import sys
import json

def hw():
    print 'Hello, world!'

def lines(fp):
    print str(len(fp.readlines()))

def get_scores():
    afinnfile = open(sys.argv[1])
    scores = {} # initialize an empty dictionary
    for line in afinnfile:
      term, score  = line.split("\t")  # The file is tab-delimited. "\t" means "tab character"
      scores[term] = int(score)  # Convert the score to an integer.
    #print scores.items() # Print every (term, score) pair in the dictionary
    return scores

def get_tweets():     
    tweets = [] # initialize an empty list
    tweet_file = open(sys.argv[1])
    for line in tweet_file:
        l_dict = json.loads(line) # loads lines as dicts
        tweets.append(l_dict) # adds dicts to list
    return tweets

def get_tags(tweets):
    tag_counts = {} # dict for hastags and their counts
    for tweet in tweets:
        if "entities" in tweet and tweet["entities"] is not None: # checks for entities/nullness
            if "hashtags" in tweet["entities"] and tweet["entities"]["hashtags"] is not None:
                for tag in tweet["entities"]["hashtags"]:
                    if tag in tag_counts: # been seen before
                        tag_counts[tag] += 1
                    else:
                        tag_counts[tga] = 1
    return tag_counts

def get_text(tweets):
    tweet_text = [] 
    for tweet in tweets: # for each tweet in the list passed to the method
        if "\'text\'" in tweet: # disambiguations of the key
            ttext = tweet["\'text\'"]
            tweet_text.append(ttext)
        if "\"text\"" in tweet:
            ttext = tweet["\"text\""]
            tweet_text.append(ttext)
        if "text" in tweet:
            ttext = tweet["text"]
            tweet_text.append(ttext)
    return tweet_text # returns a list of the texts of each tweet
                
def get_sent(tweet_text, scores):
    tweet_scores = []
    for text in tweet_text: # iterate over all tweets
        text_list = text.split() # split tweets based on whitespace
        tweet_score = 0 # initialize a score of 0 for all tweets
        for i in range(0,len(text_list)):
            text_list[i] = text_list[i].strip(".,!?:;\"\'") # strip all punctuation
            if text_list[i] in scores: # if the word is in scores, then add its score to tweet_score
                tweet_score += scores[text_list[i]]
        tweet_scores.append(tweet_score) # add the overall tweet's score to the list
    return tweet_scores
        
def get_new_sent(tweet_text, scores):
    tweet_scores = get_sent(tweet_text, scores)
    new_sent = {} # initialize a new dict
    pos_count = {} # dict for positive counts
    neg_count = {} # dict for negative counts
    for i in range(0,len(tweet_scores)): # iterate over all tweets/scores
        text_list = tweet_text[i].split()
        for j in range(0,len(text_list)):
            text_list[j] = text_list[j].strip(".,!?:;\"\'")
            if text_list[j] not in scores: # if the word is not scored
                new_sent[text_list[j]] = 0 # adds the word to dict and sets score to 0
                if tweet_scores[i] >= 0: # if positive increment pos count
                    if text_list[j] not in pos_count: # if not seen positively before
                        pos_count[text_list[j]] = 1
                    else:
                        pos_count[text_list[j]] += 1
                elif tweet_scores[i] < 0: # if negative increment neg count
                    if text_list[j] not in neg_count: # if not seen negatively before
                        neg_count[text_list[j]] = 1
                    else:
                        neg_count[text_list[j]] += 1
    for word in new_sent:
        if word in pos_count: # if the word has been associated positively
            if word in neg_count: # if the word has also been associated negatively
                new_sent[word] = pos_count[word] / neg_count[word]
            else:
                new_sent[word] = pos_count[word]
        if word in neg_count: # if the word has only been associated negatively
            if word in pos_count: # just in case something passed through that shouldn't have?
                new_sent[word] = pos_count[word] / neg_count[word]
            else:
                new_sent[word] = neg_count[word]
    return new_sent

def freq(tweet_text):
    frequencies = {} # initialize a new dict for frequencies
    counts = {} # new dict for word counts
    all_count = 0
    for text in tweet_text: # iterate over all tweets
        text_list = text.split() # split tweets based on whitespace
        for i in range(0,len(text_list)):
            text_list[i] = text_list[i].strip(".,!?:;\"\'") # strip all punctuation
            if text_list[i] in counts: # if it has been counted before
                counts[text_list[i]] += 1 # increment the count
            else: # if not, then we start its count
                counts[text_list[i]] = 1
            all_count += 1 # for every term in every tweet increment the count
    for key in counts.iterkeys():
        frequencies[key] = float(counts[key])/float(all_count)
    
    return frequencies      
            
def main():
    #sent_file = open(sys.argv[1])
    tweet_file = open(sys.argv[1])
    #scores = get_scores()
    tweets = get_tweets()
    tweet_text = get_text(tweets)
    #tweet_scores = get_sent(tweet_text, scores)
    #new_sent = get_new_sent(tweet_text, scores)
    frequencies = freq(tweet_text)
    total = 0
    for key in frequencies.iterkeys():
        print key + " " + str(frequencies[key])
        total += frequencies[key]
    #print str(total)
    #hw()
    #lines(sent_file)
    #lines(tweet_file)
    #sent_file.close()
    tweet_file.close()

if __name__ == '__main__':
    main()
