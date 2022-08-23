# Python program to generate WordCloud
 
# importing all necessary modules
from ast import Break
from wordcloud import WordCloud
import matplotlib.pyplot as plt
import wordcloud
import sys, os.path

def main():
    op = int(sys.argv[2])

    ###### plot the WordCloud image #######                      
    fig = plt.figure(figsize = (9,5), facecolor = None)
    if(op == 1 or op == 0):
        ###### Reads file #######
        file_type1 = sys.argv[1] + '.type1'
        wordcloud1 = plot(file_type1, sys.argv[3])
        if(op == 0):
            fig.add_subplot(1, 2, 1)
        plt.imshow(wordcloud1)
        plt.axis("off")
        plt.tight_layout(pad = 2)
        plt.title("Type 1", fontsize=18) 

    if(op == 2 or op == 0):
        ###### Reads file #######
        file_type2 = sys.argv[1] + '.type2'
        wordcloud2 = plot(file_type2, sys.argv[3])
        if(op == 0):
            fig.add_subplot(1, 2, 2)
        plt.imshow(wordcloud2)
        plt.axis("off")
        plt.tight_layout(pad = 2)
        plt.title("Type 2", fontsize=18)
        plt.savefig(os.path.join(sys.argv[4], 'word_cloud.png'))
        
    plt.show()

def plot(file_type, op_k):
    with open(file_type) as f:
        content = f.readlines()
    comment_words = {}
    for x in content:
        a, b = x.split()
        comment_words.update({b: int(a)})

    if(len(comment_words) == 0):
        print("Repetitions less than x.")
        exit()

    wordcloud = WordCloud(width = 1000, height = 900,
                    background_color ='white',
                    colormap = 'inferno',
                    min_font_size = 1,
                    max_words = int(op_k))

    wordcloud.fit_words(comment_words)
    return wordcloud

if __name__ == '__main__':
    main()