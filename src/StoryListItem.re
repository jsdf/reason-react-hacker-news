open Utils;

requireCSS("src/StoryListItem.css");

let commentIcon = requireAssetURI("src/comment.png");

let component = ReasonReact.statelessComponent("StoryListItem");
let make = (~story: StoryData.story, ~index: int, _children) => {

  let renderTitle = () => {
    let content =
      <div className="StoryListItem_storyTitle">
        (intEl(index + 1))
        (textEl(". "))
        <span className="StoryListItem_storyTitleText"> (textEl(story.title)) </span>
      </div>;

    <div>
      (
        switch story.url {
        | Some(url) => <a href=url className="StoryListItem_link"> content </a>
        | None =>
          <Link href=("/comments/" ++ string_of_int(story.id)) className="StoryListItem_link">
            content
          </Link>
        }
      )
    </div>
  };

  let renderByline = () =>
    <div className="StoryListItem_row StoryListItem_byline">
      /* TODO: badge */

        <span className="StoryListItem_number"> (intEl(story.score)) </span>
        (textEl(" points"))
        <span>
          <span className="StoryListItem_storyTime">
            ({
              let time = story.time;
              let by = story.by;
              textEl({j| submitted $time by $by|j})
            })
          </span>
        </span>
      </div>;

  let renderArticleButton = () =>
    <div className="StoryListItem_flexRow">
      <div className="StoryListItem_storyCell"> (renderTitle()) (renderByline()) </div>
    </div>;

  let renderCommentsButton = () =>
    <div className="StoryListItem_commentsCell">
      <Link href=("/comments/" ++ string_of_int(story.id)) className="StoryListItem_link">
        <div> <img alt="comments" className="StoryListItem_icon" src=commentIcon /> </div>
        <div>
          <span className="StoryListItem_commentsText">
            <span className="StoryListItem_number"> (intEl(story.descendants)) </span>
            (textEl(" comments"))
          </span>
        </div>
      </Link>
    </div>;

  {
    ...component,
    render: (_self) =>
      <div className="StoryListItem_itemRow">
        (renderArticleButton())
        (renderCommentsButton())
      </div>
  }
};
