HTMLElement.prototype.findChildrenByClassName = function (className) {
	var result = [];

	this.childNodes.forEach((ele, index) => {
		if (ele.className === className) {
			result.push(ele);
		}
	});

	return result;
}

export class Slider extends React.Component {
	constructor(props) {
		super(props);

		this.state = {
			curIndex: this.props.curIndex
		};

		this.handleKeyup = this.handleKeyup.bind(this);
		this.navigate = this.navigate.bind(this);
		this.dir = '';
	}

	handleKeyup(ev) {
		var keyCode = ev.keyCode || ev.which;
		switch (keyCode) {
			case 37:
				this.navigate('left');
				break;
			case 39:
				this.navigate('right');
				break;
					}
	}

	componentDidMount() {
		document.addEventListener('keyup', this.handleKeyup);
	}

	componentWillUnmount() {
		document.removeEventListener('keyup', this.handleKeyup);
	}

	shouldComponentUpdate(nextProps, nextState) {
		return this.state.curIndex !== nextState.curIndex;
	}

	componentDidUpdate() {
		var nextItem = this.refs['item__' + this.state.curIndex];
		var nextTitle = nextItem.findChildrenByClassName('title')[0];
		var nextDescription = nextItem.findChildrenByClassName('description')[0];

		/** set the right properties for the next element to come in */
		dynamics.css(nextItem, { opacity: 1, visibility: 'visible' });
		dynamics.css(nextTitle, {
			opacity: 0,
			translateX: this.dir === 'right' ? nextTitle.offsetWidth / 2 : -1 * nextTitle.offsetWidth / 2,
			rotateZ: this.dir === 'right' ? 10 : -10
		});

		/** animate the next title in */
		dynamics.animate(nextTitle, { opacity: 1, translateX: 0 }, {
			type: dynamics.spring,
			duration: 2000,
			friction: 600,
			complete: function() {
			}
		});

		/** set the right properties for the next description to come in */
		dynamics.css(nextDescription, {
			translateX: this.dir === 'right' ? 250 : -250,
			opacity: 0
		});

		/** animate the next description in */
		dynamics.animate(nextDescription, { translateX: 0, opacity: 1 }, {
			type: dynamics.bezier,
			points: [{ "x": 0, "y": 0, "cp": [{ "x": 0.2, "y": 1 }]}, { "x": 1, "y": 1, "cp": [{ "x": 0.3, "y": 1 }] }],
			duration: 650
		});
	}

	navigate(dir) {
		this.dir = dir;

		var total = this.props.items.length;
		var current = this.state.curIndex;
		var curItem = this.refs['item__' + current];
		var curTitle = curItem.findChildrenByClassName('title')[0];
		var curDescription = curItem.findChildrenByClassName('description')[0];
		var next = this.dir === 'right' ? ((current + 1) % total) : ((current - 1 < 0 ? (current + total -1) % total : current - 1));

		/** animate the current title out */
		dynamics.animate(curTitle, {
			opacity: 0,
			translateX: this.dir === 'right' ? -1 * curTitle.offsetWidth / 2 : curTitle.offsetWidth / 2,
			rotateZ: this.dir === 'right' ? -10 : 10
		}, {
			type: dynamics.spring,
			duration: 2000,
			friction: 600,
			complete: function() {
				dynamics.css(curItem, {
					opacity: 0,
					visibility: 'hidden'
				});
			}
		});

		/** animate the current description out */
		dynamics.animate(curDescription, {
			translateX: this.dir === 'right' ? -250 : 250,
			opacity: 0
		}, {
			type: dynamics.bezier,
			points: [{ "x": 0, "y": 0, "cp": [{ "x": 0.2, "y": 1}]	}, {	"x": 1, "y": 1, "cp": [{ "x": 0.3, "y": 1 }]	}],
			duration: 450
		});

		setTimeout(function () {
			this.setState({
				curIndex: next
			});
		}.bind(this), 200);
	}

	render() {
		var items = [];
		this.props.items.forEach((ele, index) => {
			items.push(<li key={index} ref={'item__' + index} className={'content__item' + (index == this.state.curIndex ? ' content__item--current' : '')}>
					<div className="title" dangerouslySetInnerHTML={{ __html: ele.title }}></div>
					<div className="description" dangerouslySetInnerHTML={{ __html: ele.description }}></div>
				</li>);
		});

		return (
			<div className="slider__container">
				<ul>
					{items}
					<li className="fa fa-angle-left" onClick={
							function () {
								this.navigate('left');
							}.bind(this)
						}></li>
					<li className="fa fa-angle-right" onClick={
							function () {
								this.navigate('right');
							}.bind(this)
						}></li>
				</ul>
			</div>
		);
	}
}

Slider.defaultProps = {
	items: [
		{
			title: 'item1',
			description: 'the item 1 of the slider'
		}, {
			title: 'item2',
			description: 'the item 2 of the slider'
		}, {
			title: 'item3',
			description: 'the item 3 of the slider'
		}
	],
	curIndex: 0
};

Slider.propTypes = {
	items: React.PropTypes.arrayOf(React.PropTypes.objectOf({
		title: React.PropTypes.string,
		description: React.PropTypes.string
	})),
	curIndex: React.PropTypes.number
};
