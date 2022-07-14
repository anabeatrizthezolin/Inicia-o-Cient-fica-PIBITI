# Python program to generate WordCloud
 
# importing all necessary modules
from wordcloud import WordCloud, STOPWORDS
import matplotlib.pyplot as plt
import wordcloud
import sys

def main():
    op = int(sys.argv[2])

    ###### plot the WordCloud image #######                      
    fig = plt.figure(figsize = (9,5), facecolor = None)
    if(op == 1 or op == 0):
        ###### Reads file #######
        file_type1 = sys.argv[1] + '.type1'
        wordcloud1 = plot(file_type1)
        if(op == 0):
            fig.add_subplot(1, 2, 1)
        plt.imshow(wordcloud1)
        plt.axis("off")
        plt.tight_layout(pad = 3.5)
        plt.title("Type 1", fontsize=15) 

    if(op == 2 or op == 0):
        ###### Reads file #######
        file_type2 = sys.argv[1] + '.type2'
        wordcloud2 = plot(file_type2)
        if(op == 0):
            fig.add_subplot(1, 2, 2)
        plt.imshow(wordcloud2)
        plt.axis("off")
        plt.tight_layout(pad = 3.5)
        plt.title("Type 2", fontsize=15)
    
    plt.show()

def plot(file_type):

    with open(file_type) as f:
        content = f.readlines()
    comment_words = {}

    #stopwords = set(STOPWORDS)
    for x in content:
        a, b = x.split()
        comment_words.update({b: int(a)})

    wordcloud = WordCloud(width = 800, height = 800,
                    background_color ='white',
                    colormap = 'Set3',
                    min_font_size = 10,
                    max_words = 100)
    wordcloud.fit_words(comment_words)

    return wordcloud

if __name__ == '__main__':
    main()