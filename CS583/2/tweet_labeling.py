import cmd
import os
import sys

def read_tweets(tweet_file, class_file):
	'''
	Writes tweets to command line and prompts for input:
	p = positive, n = negative, m = mixed, o = neutral
	'''
	tweets = open(os.getcwd() + '/' + tweet_file, 'r+')
	classed_tweets = open(os.getcwd() + '/' + class_file, 'w+')
	n = 1
	prompts = {
		'p' : 'positive',
		'n' : 'negative',
		'm' : 'mixed',
		'o' : 'neutral'
	}

	for line in tweets:
		prompt_string = str(n) + ': p = positive, n = negative, m = mixed, o = neutral, q = quit '
		c = raw_input('\n' + line + '\n' + prompt_string + '->> ')
		try:
			if c == 'q':
				tweets.close()
				classed_tweets.close()
				sys.exit(0)
			else:
				classed_tweets.write(line.strip() + '@@' + prompts[c] + '\n')
		except KeyError:
			c = raw_input(line + '\n' + prompt_string + '->> ')
		n += 1

	tweets.close()
	classed_tweets.close()

def compare_ratings(al_file, rk_file, consensus, discrepant):
	'''
	Compares ratings between two files
	'''
	al = open(os.getcwd() + '/' + al_file, 'r+')
	rk = open(os.getcwd() + '/' + rk_file, 'r+')
	consensus = open(os.getcwd() + '/' + consensus, 'w+')
	discrepant = open(os.getcwd() + '/' + discrepant, 'w+')

	tweets = []
	al_c = []
	rk_c = []
	agreement = []

	for line in al:
		line_split = line.split('@@')
		try:
			al_c.append(line_split[1].strip())
		except IndexError:
			al_c.append('')

	for line in rk:
		line_split = line.split('@@')
		tweets.append(line_split[0])
		try:
			rk_c.append(line_split[1].strip())
		except IndexError:
			rk_c.append('')

	for i in range(0, len(tweets)):
		a = al_c[i] if al_c[i] == rk_c[i] else 0
		agreement.append(a)
	
	tweet_classes = dict(zip(tweets, agreement))
	al_c_dict = dict(zip(tweets, al_c))
	rk_c_dict = dict(zip(tweets, rk_c))

	c_length = 0
	d_length = 0

	for tweet in tweets:
		if tweet_classes[tweet] == 0:
			# d = raw_input(str(al_c_dict[tweet]) + '\t@@\t' + rk_c_dict[tweet] + '->>')
			discrepant.write(tweet + '@@' + al_c_dict[tweet] + '@@' + rk_c_dict[tweet] + '\n')
			d_length += 1
		else:
			consensus.write(tweet + '@@' + tweet_classes[tweet] + '\n')
			c_length += 1

	print 'Discrepant Tweets:\t' + str(d_length) + '\n' + 'Consensus Tweets:\t' + str(c_length) + '\n'

	al.close()
	rk.close()
	consensus.close()
	discrepant.close()

def resolve_discrepancies(discrepant, resolved):
	dis = open(os.getcwd() + '/' + discrepant, 'r+')
	res = open(os.getcwd() + '/' + resolved, 'w+')

	for line in dis:
		line_split = line.split('@@')
		tweet = line_split[0]
		al = line_split[1]
		rk = line_split[2]
		i = raw_input(tweet + '\n\n1: ' + al + '\tOR\t2: ' + rk + '->> ')
		if i == '1':
			res.write(tweet + '@@' + al)
		elif i == '2':
			res.write(tweet + '@@' + rk)
		else:
			i = raw_input('1: ' + al + '\tOR\t2: ' + rk)

	dis.close()
	res.close()


def main():
	# read_tweets('12.txt', '12_rk.txt')
	# compare_ratings('12_al.txt', '12_rk.txt', '12_c.txt', '12_d.txt')
	resolve_discrepancies('12_d.txt', '12_r.txt')

if __name__ == "__main__":
	main()
